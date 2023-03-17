package org.citra.citra_emu.ui.main;

import android.content.Intent;
import android.os.Bundle;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.Toast;

import androidx.activity.result.ActivityResultLauncher;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.splashscreen.SplashScreen;

import org.citra.citra_emu.CitraApplication;
import org.citra.citra_emu.NativeLibrary;
import org.citra.citra_emu.R;
import org.citra.citra_emu.activities.EmulationActivity;
import org.citra.citra_emu.contracts.OpenDocumentTreeResultContract;
import org.citra.citra_emu.contracts.OpenFileResultContract;
import org.citra.citra_emu.features.settings.ui.SettingsActivity;
import org.citra.citra_emu.model.GameProvider;
import org.citra.citra_emu.ui.platform.PlatformGamesFragment;
import org.citra.citra_emu.utils.AddDirectoryHelper;
import org.citra.citra_emu.utils.BillingManager;
import org.citra.citra_emu.utils.DirectoryInitialization;
import org.citra.citra_emu.utils.FileBrowserHelper;
import org.citra.citra_emu.utils.PermissionsHandler;
import org.citra.citra_emu.utils.PicassoUtils;
import org.citra.citra_emu.utils.StartupHandler;
import org.citra.citra_emu.utils.ThemeUtil;

import java.util.Collections;

/**
 * The main Activity of the Lollipop style UI. Manages several PlatformGamesFragments, which
 * individually display a grid of available games for each Fragment, in a tabbed layout.
 */
public final class MainActivity extends AppCompatActivity implements MainView {
    private Toolbar mToolbar;
    private int mFrameLayoutId;
    private PlatformGamesFragment mPlatformGamesFragment;

    private MainPresenter mPresenter = new MainPresenter(this);

    // Singleton to manage user billing state
    private static BillingManager mBillingManager;

    private static MenuItem mPremiumButton;

    private final ActivityResultLauncher<Integer> mOpenCitraDirectory = registerForActivityResult(new OpenDocumentTreeResultContract(), result -> {
        if (result == null || !PermissionsHandler.setCitraDirectory(result.getDataString())) return;
        int takeFlags = (Intent.FLAG_GRANT_WRITE_URI_PERMISSION | Intent.FLAG_GRANT_READ_URI_PERMISSION);
        getContentResolver().takePersistableUriPermission(result.getData(), takeFlags);
        CitraApplication.documentsTree.setRoot(PermissionsHandler.getCitraDirectory());

        DirectoryInitialization.resetCitraDirectoryState();
        DirectoryInitialization.start(getApplicationContext());

        if (mPlatformGamesFragment == null) {
            mPlatformGamesFragment = new PlatformGamesFragment();
            getSupportFragmentManager().beginTransaction().add(mFrameLayoutId, mPlatformGamesFragment)
                    .commit();
        }
    });

    private final ActivityResultLauncher<Integer> mOpenGameListLauncher = registerForActivityResult(new OpenDocumentTreeResultContract(), result -> {
        if (result == null) return;
        int takeFlags = (Intent.FLAG_GRANT_WRITE_URI_PERMISSION | Intent.FLAG_GRANT_READ_URI_PERMISSION);
        getContentResolver().takePersistableUriPermission(result.getData(), takeFlags);
        // When a new directory is picked, we currently will reset the existing games
        // database. This effectively means that only one game directory is supported.
        // TODO(bunnei): Consider fixing this in the future, or removing code for this.
        getContentResolver().insert(GameProvider.URI_RESET, null);
        // Add the new directory
        mPresenter.onDirectorySelected(result.getDataString());
    });

    private final ActivityResultLauncher<Pair<Boolean, Integer>> mOpenFileLauncher = registerForActivityResult(new OpenFileResultContract(), result -> {
        if (result == null) return;
        String[] selectedFiles = FileBrowserHelper.getSelectedFiles(result, getApplicationContext(), Collections.singletonList("cia"));
        if (selectedFiles == null) {
            Toast.makeText(getApplicationContext(), R.string.cia_file_not_found, Toast.LENGTH_LONG).show();
            return;
        }
        NativeLibrary.InstallCIAS(selectedFiles);
        mPresenter.refreshGameList();
    });

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SplashScreen splashScreen = SplashScreen.installSplashScreen(this);
        splashScreen.setKeepOnScreenCondition(() -> !DirectoryInitialization.areCitraDirectoriesReady());

        ThemeUtil.applyTheme(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViews();

        setSupportActionBar(mToolbar);

        mFrameLayoutId = R.id.games_platform_frame;
        mPresenter.onCreate();

        if (savedInstanceState == null) {
            StartupHandler.HandleInit(this, mOpenCitraDirectory);
            if (PermissionsHandler.hasWriteAccess(this)) {
                mPlatformGamesFragment = new PlatformGamesFragment();
                getSupportFragmentManager().beginTransaction().add(mFrameLayoutId, mPlatformGamesFragment)
                        .commit();
            }
        } else {
            mPlatformGamesFragment = (PlatformGamesFragment) getSupportFragmentManager().getFragment(savedInstanceState, "mPlatformGamesFragment");
        }
        PicassoUtils.init();

        // Setup billing manager, so we can globally query for Premium status
        mBillingManager = new BillingManager(this);

        // Dismiss previous notifications (should not happen unless a crash occurred)
        EmulationActivity.tryDismissRunningNotification(this);
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        if (PermissionsHandler.hasWriteAccess(this)) {
            if (getSupportFragmentManager() == null) {
                return;
            }
            if (outState == null) {
                return;
            }
            getSupportFragmentManager().putFragment(outState, "mPlatformGamesFragment", mPlatformGamesFragment);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        mPresenter.addDirIfNeeded(new AddDirectoryHelper(this));
    }

    // TODO: Replace with a ButterKnife injection.
    private void findViews() {
        mToolbar = findViewById(R.id.toolbar_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu_game_grid, menu);
        mPremiumButton = menu.findItem(R.id.button_premium);

        if (mBillingManager.isPremiumCached()) {
            // User had premium in a previous session, hide upsell option
            setPremiumButtonVisible(false);
        }

        return true;
    }

    static public void setPremiumButtonVisible(boolean isVisible) {
        if (mPremiumButton != null) {
            mPremiumButton.setVisible(isVisible);
        }
    }

    /**
     * MainView
     */

    @Override
    public void setVersionString(String version) {
        mToolbar.setSubtitle(version);
    }

    @Override
    public void refresh() {
        getContentResolver().insert(GameProvider.URI_REFRESH, null);
        refreshFragment();
    }

    @Override
    public void launchSettingsActivity(String menuTag) {
        if (PermissionsHandler.hasWriteAccess(this)) {
            SettingsActivity.launch(this, menuTag, "");
        } else {
            PermissionsHandler.checkWritePermission(this, mOpenCitraDirectory);
        }
    }

    @Override
    public void launchFileListActivity(int request) {
        if (PermissionsHandler.hasWriteAccess(this)) {
            switch (request) {
                case MainPresenter.REQUEST_SELECT_CITRA_DIRECTORY:
                    mOpenCitraDirectory.launch(R.string.select_citra_user_folder);
                    break;
                case MainPresenter.REQUEST_ADD_DIRECTORY:
                    mOpenGameListLauncher.launch(R.string.select_game_folder);
                    break;
                case MainPresenter.REQUEST_INSTALL_CIA:
                    mOpenFileLauncher.launch(new Pair<>(true, R.string.install_cia_title));
                    break;
            }
        } else {
            PermissionsHandler.checkWritePermission(this, mOpenCitraDirectory);
        }
    }

    /**
     * Called by the framework whenever any actionbar/toolbar icon is clicked.
     *
     * @param item The icon that was clicked on.
     * @return True if the event was handled, false to bubble it up to the OS.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return mPresenter.handleOptionSelection(item.getItemId());
    }

    private void refreshFragment() {
        if (mPlatformGamesFragment != null) {
            mPlatformGamesFragment.refresh();
        }
    }

    @Override
    protected void onDestroy() {
        EmulationActivity.tryDismissRunningNotification(this);
        super.onDestroy();
    }

    /**
     * @return true if Premium subscription is currently active
     */
    public static boolean isPremiumActive() {
        return mBillingManager.isPremiumActive();
    }

    /**
     * Invokes the billing flow for Premium
     *
     * @param callback Optional callback, called once, on completion of billing
     */
    public static void invokePremiumBilling(Runnable callback) {
        mBillingManager.invokePremiumBilling(callback);
    }
}
