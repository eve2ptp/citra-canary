package org.citra.citra_emu.contracts;

import android.content.Context;
import android.content.Intent;
import android.os.Environment;

import androidx.activity.result.contract.ActivityResultContract;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.documentfile.provider.DocumentFile;

public class OpenDocumentTreeResultContract extends ActivityResultContract<Integer, Intent> {
    @NonNull
    @Override
    public Intent createIntent(@NonNull Context context, Integer title) {
        return new Intent(Intent.ACTION_OPEN_DOCUMENT_TREE).putExtra(Intent.EXTRA_TITLE, title);
    }

    @Override
    public Intent parseResult(int i, @Nullable Intent intent) {
        return intent;
    }
}
