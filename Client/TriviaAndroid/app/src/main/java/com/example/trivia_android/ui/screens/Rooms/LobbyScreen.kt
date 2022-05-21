package com.example.trivia_android.ui.screens.Rooms

import android.content.res.Configuration.UI_MODE_NIGHT_YES
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AccountCircle
import androidx.compose.material.icons.filled.SupervisedUserCircle
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.focus.focusModifier
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import kotlinx.coroutines.delay


@Composable
fun PlayerList(
    modifier: Modifier = Modifier,
    playerList: List<String>,
) {

    Card(modifier, elevation = 12.dp) {

        Column(modifier = Modifier.padding(8.dp)) {

            Text(
                "Players: ${playerList.size}",
                style = MaterialTheme.typography.subtitle1,
                modifier = Modifier.padding(bottom = 4.dp)
            )

            Divider(modifier = Modifier.fillMaxWidth(0.9f), thickness = 1.dp)


            LazyColumn {

                itemsIndexed(playerList) { index: Int, it: String ->

                    Row {
                        Icon(
                           if(index == 0) Icons.Filled.SupervisedUserCircle else Icons.Filled.AccountCircle,
                           "User Icon",
                            modifier = Modifier
                                .padding(end = 4.dp)
                                .align(Alignment.CenterVertically)
                        )

                        Text(if(index == 0) "$it (Admin)" else it, modifier = Modifier
                            .padding(4.dp)
                            .align(Alignment.CenterVertically))
                    }

                    if(index != playerList.lastIndex) Divider(modifier = Modifier.fillMaxWidth(0.9f), thickness = 1.dp)

                }
            }
        }

    }
}




@Composable
fun LobbyScreen(
    modifier: Modifier = Modifier,
    roomName: String,
    playerAmount: String,
    ansTime: String,
    questionAmount: String,
    playerList: List<String>,
    onRefresh: () -> Unit = { }
) {


    Scaffold(
        topBar = {
            TopAppBar(backgroundColor = MaterialTheme.colors.surface) {
                Text("Room: $roomName", style = MaterialTheme.typography.subtitle2)
            }
        },


        floatingActionButton = {
            FloatingActionButton(
                onClick = {  },
                backgroundColor = Color.Transparent,
                modifier = Modifier.background(
                    brush = Brush.horizontalGradient(
                        listOf(
                            MaterialTheme.colors.primary,
                            MaterialTheme.colors.secondary
                        ),
                    ),
                    shape = MaterialTheme.shapes.small,
                    alpha = 0.9f
                ),

            ) {

                Text("Start Game", modifier = Modifier.padding(4.dp))

            }
        }

    ) {

        Column(modifier = modifier) {

            Text(
                "Room Info: ",
                style = MaterialTheme.typography.h3,
                modifier = Modifier.padding(16.dp)
            )


            Row(modifier = Modifier
                .padding(bottom = 32.dp)
                .align(Alignment.CenterHorizontally)) {

                InfoField(field = "Time", value = "$ansTime S")

                InfoField(field = "Size", value = "$playerAmount P")

                InfoField(field = "Questions", value = "$questionAmount Q")

            }



            PlayerList(
                Modifier
                    .align(Alignment.CenterHorizontally)
                    .fillMaxHeight(0.8f),
                playerList
            )
        }


        LaunchedEffect(Unit) {
            while (true) {
                onRefresh()
                delay(60000)
            }
        }


    }
}




@Composable
fun InfoField(
    modifier: Modifier = Modifier,
    field: String,
    value: String
) {

    Column(modifier = modifier.padding(8.dp)) {

        Text(
            "${field}:",
            style = MaterialTheme.typography.caption,
            fontSize = 30.sp,
            modifier = Modifier.padding(5.dp)
        )

        Text(
            value,
            style = MaterialTheme.typography.body1,
            fontSize = 30.sp,
            modifier = Modifier
                .align(Alignment.CenterHorizontally)
        )
    }
}



@Composable
@Preview
fun InfoFieldPreview() {

    TriviaAndroidTheme {

        InfoField(field = "Time", value = "60 S")

    }
}








@Composable
@Preview
fun PlayerListPreview() {

    TriviaAndroidTheme {

        PlayerList(
            modifier = Modifier.fillMaxHeight(0.5f),
            playerList = listOf(
                "Gal",
                "hahahaha",
                "David",
                "Nir",
                "a",
                "b",
                "c",
                "d",
                "e",
                "f",
                "asgdshsdhdshsh"
        ))

    }
}



@Composable
@Preview
@Preview(
    name = "Dark Mode Preview",
    uiMode = UI_MODE_NIGHT_YES
)
fun LobbyScreenPreview() {
    TriviaAndroidTheme {
        LobbyScreen(
            Modifier,
            "My Room",
            "15",
            "60",
            "10",
            listOf(
                "Gal",
                "a",
                "b",
                "c",
                "d",
                "e",
                "f",
                "asgdshsdhdshsh"
            )
        )
    }
}

