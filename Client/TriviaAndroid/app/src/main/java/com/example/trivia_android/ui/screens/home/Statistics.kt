package com.example.trivia_android.ui.screens.home

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.*
import androidx.compose.material.Card
import androidx.compose.material.Icon
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.TaskAlt
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.vector.ImageVector
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

    Card(modifier = modifier.fillMaxWidth()) {

        Row() {
            Icon(
                statIcon,
                "Statistic's icon",
                modifier = Modifier
                    .size(20.dp)
                    .align(Alignment.CenterVertically)
                    .padding(start = 3.dp)
            )

            Column() {
                Text(
                    text = value.toString(),
                    modifier = Modifier
                        .padding(12.dp)
                        .align(Alignment.CenterHorizontally),
                    style = MaterialTheme.typography.body1
                )
                Text(
                    text = name,
                    modifier = Modifier
                        .padding(start = 20.dp)
                        .align(Alignment.CenterHorizontally),
                    style = MaterialTheme.typography.body1
                )
            }



        }

    }
}

@Composable
@Preview
fun statCardPreview() {
    TriviaAndroidTheme() {
        StatCard(value = 10000.0f, name = "Hello", statIcon = Icons.Filled.TaskAlt)
    }
}