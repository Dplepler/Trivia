package com.example.trivia_android.ui.screens.home

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.*
import androidx.compose.material.Card
import androidx.compose.material.Icon
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.focus.FocusRequester.Companion.createRefs
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.BusinessLogic.ViewModels.StatIndex
import com.example.trivia_android.BusinessLogic.ViewModels.Stats
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import java.text.DecimalFormat
import java.text.DecimalFormatSymbols
import java.util.*

@Composable
fun StatCard(
    modifier: Modifier = Modifier,
    value: Float,
    name: String,
    statIcon: ImageVector
) {

    val otherSymbols = DecimalFormatSymbols(Locale.US)
    val df = DecimalFormat("#.##########", otherSymbols)

    Card(modifier = modifier, elevation = 8.dp) {

        Row() {
            Icon(
                statIcon,
                "Statistic's icon",
                modifier = Modifier
                    .size(45.dp)
                    .align(Alignment.CenterVertically)
                    .padding(start = 3.dp)
            )

            Column(modifier = Modifier.align(Alignment.CenterVertically).fillMaxWidth().padding(end = 8.dp)) {
                Text(
                    text = df.format(value),
                    modifier = Modifier
                        .align(Alignment.CenterHorizontally),
                    style = MaterialTheme.typography.h4
                )
                Text(
                    text = name,
                    modifier = Modifier

                        .align(Alignment.CenterHorizontally),
                    style = MaterialTheme.typography.h5
                )
            }
        }
    }
}

@Composable
fun StatScreenContent(
    stats: Stats = Stats()
) {
    Column() {

        Text(
            text = "Statistics",
            modifier = Modifier
                .align(Alignment.CenterHorizontally),
            style = MaterialTheme.typography.h4

        )

        StatCard(value = stats.statistics[StatIndex.gamesPlayed.index].toFloat(), name = "Games played", statIcon = Icons.Filled.QuestionAnswer,
            modifier = Modifier.padding(8.dp))
        StatCard(value = stats.statistics[StatIndex.avgTime.index].toFloat(), name = "Average answer time", statIcon = Icons.Filled.Timer,
            modifier = Modifier.padding(8.dp))
        StatCard(value = stats.statistics[StatIndex.correctAns.index].toFloat(), name = "Correct answers", statIcon = Icons.Filled.CheckCircle,
            modifier = Modifier.padding(8.dp))
        StatCard(value = stats.statistics[StatIndex.totalAns.index].toFloat(), name = "Total answers", statIcon = Icons.Filled.ModeEdit,
            modifier = Modifier.padding(8.dp))
    }
}

@Composable
@Preview
fun StatisticsScreenInit() {


    TriviaAndroidTheme() {
        Column() {
            StatCard(value = 0f, name = "Games played", statIcon = Icons.Filled.QuestionAnswer,
                modifier = Modifier.padding(8.dp))
            StatCard(value = 0f, name = "Average answer time", statIcon = Icons.Filled.Timer,
                modifier = Modifier.padding(8.dp))
            StatCard(value = 0f, name = "Total answers", statIcon = Icons.Filled.ModeEdit,
                modifier = Modifier.padding(8.dp))
        }

    }
}