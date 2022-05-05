package com.example.trivia_android.ui.screens.home




import android.content.res.Configuration.UI_MODE_NIGHT_YES
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Alignment.Companion.CenterVertically
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.painter.Painter
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import com.example.trivia_android.R


@Composable
fun RoomCard(
    modifier: Modifier = Modifier,
    roomText: String,
    buttonText: String,
    roomImage: Painter,
    buttonIcon: ImageVector,

    ) {

    Card(
        modifier = modifier
    ) {


        Column(modifier = Modifier.padding(8.dp)) {


            Row(modifier = Modifier.padding(top = 24.dp, bottom = 36 .dp)) {

                Image(
                    roomImage,
                    "Room Icon",
                    modifier = Modifier
                        .size(150.dp)
                        .align(CenterVertically)
                        .padding(start = 20.dp)
                )

                Text(
                    text = roomText,
                    modifier = Modifier
                        .align(CenterVertically)
                        .padding(start = 30.dp, end = 20.dp),
                    style = MaterialTheme.typography.h4
                )

            }


            Button(onClick = { /*TODO*/ }, modifier = Modifier.padding(8.dp)) {

                Text(buttonText, modifier = Modifier.padding(end = 36.dp))

                Icon(buttonIcon, "Button Icon")

            }

        }

    }

}



@Preview
@Preview(
    name = "Dark Mode Preview",
    uiMode = UI_MODE_NIGHT_YES
)
@Composable
fun RoomCardPreview() {

    TriviaAndroidTheme{

        RoomCard(
            Modifier,
            "Create\nRoom",
            "Create a new game room!",
            painterResource(id = R.drawable.ic_createroomicon),
            Icons.Filled.Add
        )

    }


}

