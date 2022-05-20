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
import com.example.trivia_android.ui.theme.TriviaAndroidTheme

@Composable
fun StatCard(
    modifier: Modifier = Modifier,
    value: Float,
    name: String,
    statIcon: ImageVector
) {

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
                    text = value.toString(),
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