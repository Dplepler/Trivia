package com.example.trivia_android.ui.screens.game.resultScreen

import android.content.res.Configuration.UI_MODE_NIGHT_YES
import android.media.Image
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.layout.*
import androidx.compose.material.Card
import androidx.compose.material.Icon
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Alarm
import androidx.compose.material.icons.filled.Cancel
import androidx.compose.material.icons.filled.CheckCircle
import androidx.compose.material.icons.filled.Timer
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import java.text.DecimalFormat
import java.text.DecimalFormatSymbols
import java.util.*


@Composable
fun StatBox(
    statIcon: ImageVector = Icons.Filled.CheckCircle,
    statValue: Float = 0f,
    modifier: Modifier = Modifier
) {


    val otherSymbols = DecimalFormatSymbols(Locale.US)
    val df = DecimalFormat("#.##########", otherSymbols)


    Card(
        border = BorderStroke(1.dp, MaterialTheme.colors.onPrimary),
        backgroundColor = MaterialTheme.colors.primary,
        modifier = modifier.height(100.dp).width(100.dp)
    ) {
        Column(
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {

            Icon(
                statIcon,
                null,
                modifier = Modifier.padding(bottom = 12.dp)
            )

            Text(df.format(statValue))

        }
    }
}



@Composable
@Preview
@Preview(
    name = "Stat Box Dark",
    uiMode = UI_MODE_NIGHT_YES
)
fun StatBoxPreview() {
    TriviaAndroidTheme {


        Row {

            StatBox(statValue = 6f)

            StatBox(statIcon = Icons.Filled.Cancel, statValue = 9f)

            StatBox(statIcon = Icons.Filled.Alarm, statValue = 6.5f)

        }

    }
}

