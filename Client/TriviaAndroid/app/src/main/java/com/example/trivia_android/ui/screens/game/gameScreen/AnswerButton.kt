package com.example.trivia_android.ui.screens.game

import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Cancel
import androidx.compose.material.icons.filled.CheckCircle
import androidx.compose.material.icons.filled.Circle
import androidx.compose.material.icons.filled.RemoveCircle
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.Green200
import com.example.trivia_android.ui.theme.Red200
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun AnswerButton(
    answerText: String = "Wrench",
    buttonIcon: ImageVector = Icons.Filled.Circle,
    backgroundColor: Color = MaterialTheme.colors.primary,
    enabled: Boolean = true,
    onClick: () -> Unit = { },
    modifier: Modifier = Modifier
) {

    Button(
        onClick = if(enabled) { onClick }  else { { } },
        colors = ButtonDefaults.buttonColors(backgroundColor = backgroundColor),
        modifier = modifier
            .border(
                BorderStroke(1.dp, MaterialTheme.colors.onPrimary),
                shape = MaterialTheme.shapes.small
            )
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth(0.8f)
                .padding(top = 8.dp, bottom = 8.dp),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {

            Icon(
                buttonIcon,
                contentDescription = null,
                tint = MaterialTheme.colors.onPrimary.copy(0.7f)
            )

            Text(answerText)

            Icon(
                buttonIcon,
                contentDescription = null,
                tint = MaterialTheme.colors.onPrimary.copy(0.7f)
            )

        }
    }
}



@Composable
fun CorrectButton(
    answerText: String = "Wrench",
    modifier: Modifier = Modifier
) {
    AnswerButton(
        answerText = answerText,
        buttonIcon = Icons.Filled.CheckCircle,
        backgroundColor = Green200,
        enabled = false,
        modifier = Modifier
    )
}



@Composable
fun IncorrectButton(
    answerText: String = "Wrench",
    modifier: Modifier = Modifier
) {
    AnswerButton(
        answerText = answerText,
        buttonIcon = Icons.Filled.Cancel,
        backgroundColor = Red200,
        enabled = false,
        modifier = Modifier
    )
}






@Composable
@Preview
fun AnswerButtonPreview() {
    TriviaAndroidTheme {

        
        Column(modifier = Modifier.fillMaxSize()) {
            AnswerButton()

            CorrectButton(answerText = "Hammer")

            IncorrectButton(answerText = "Drill")
        }

        

    }
}


