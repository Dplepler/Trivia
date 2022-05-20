package com.example.trivia_android.ui.screens.Rooms

import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AccountCircle
import androidx.compose.material.icons.filled.SupervisedUserCircle
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun PlayerList(
    modifier: Modifier = Modifier,
    playerList: List<String>,
) {

    Card(modifier, elevation = 12.dp) {

        Column(modifier = Modifier.padding(8.dp)) {

            Text(
                "Players",
                style = MaterialTheme.typography.subtitle1,
                modifier = Modifier.padding(bottom = 4.dp)
            )

            Divider(modifier = Modifier.fillMaxWidth(), thickness = 1.dp)


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

                        Text(it, modifier = Modifier
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