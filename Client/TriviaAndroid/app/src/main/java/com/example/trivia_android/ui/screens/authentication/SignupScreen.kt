package com.example.trivia_android.ui.screens.authentication

import android.content.res.Configuration.UI_MODE_NIGHT_YES
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AppRegistration
import androidx.compose.material.icons.filled.Login
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Shape
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.SharedComponents.SharpTextField
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun SignupScreenContent(
    modifier: Modifier = Modifier,
    usernameText: MutableState<String>,
    passwordText: MutableState<String>,
    emailText: MutableState<String>,
    onClickSignup: () -> Unit = { },
    onClickSwitch: () -> Unit = { },
    onSuccessSignup: () -> Unit = { },
    status: MutableState<Int> = mutableStateOf(0)
) {

    if(status.value == 1) { onSuccessSignup() }

    Scaffold(

        topBar = { TopAppBar(
            backgroundColor = if(isSystemInDarkTheme()) MaterialTheme.colors.surface else MaterialTheme.colors.secondary,
            modifier = modifier.clip(RoundedCornerShape(bottomStart = 4.dp, bottomEnd = 4.dp))
        ) {
            Text(
                "Signup",
                style = MaterialTheme.typography.subtitle2,
                modifier = modifier.padding(start = 10.dp)
            )
        }},


        floatingActionButton = {
            FloatingActionButton(
                onClick = { onClickSwitch() },
                backgroundColor = MaterialTheme.colors.secondaryVariant
            ) {
                Row(modifier = modifier.padding(8.dp)) {
                    Icon(Icons.Filled.Login, contentDescription = "Signup Icon")
                    Text("Login")
                }
            }
        }
    ) {
        Column(modifier = modifier.fillMaxSize()) {

            SharpTextField(
                modifier = modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 150.dp),
                color = MaterialTheme.colors.secondary,
                stringState = usernameText,
                label = "Username"
            )


            SharpTextField(
                modifier = modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 40.dp),
                color = MaterialTheme.colors.secondary,
                stringState = passwordText,
                label = "Password"
            )


            SharpTextField(
                modifier = modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 40.dp),
                color = MaterialTheme.colors.secondary,
                stringState = emailText,
                label = "email"
            )


            Button(
                onClick = { onClickSignup() },
                colors = ButtonDefaults.buttonColors(
                    backgroundColor = MaterialTheme.colors.secondary
                ),
                enabled = (
                        !usernameText.value.isEmpty() &&
                                !passwordText.value.isEmpty() &&
                                !emailText.value.isEmpty()
                        ),
                modifier = modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 32.dp)
            ) {
                Text(
                    "Signup",
                    modifier = Modifier.padding(
                        start = 16.dp,
                        end = 16.dp,
                        top = 4.dp,
                        bottom = 4.dp
                    )
                )
            }

        }
    }

}



@Composable
@Preview
@Preview(
    name = "dark theme signup",
    uiMode = UI_MODE_NIGHT_YES
)
fun SignupPreview() {
    val usernameText = remember { mutableStateOf("") }
    val passwordText = remember { mutableStateOf("") }
    val emailText = remember { mutableStateOf("") }
    TriviaAndroidTheme {
        SignupScreenContent(
            usernameText = usernameText,
            passwordText = passwordText,
            emailText = emailText
        )
    }
}
