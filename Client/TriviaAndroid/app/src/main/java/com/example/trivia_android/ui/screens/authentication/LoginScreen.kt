package com.example.trivia_android.ui.screens.authentication

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AppRegistration
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun LoginScreenContent(
    modifier: Modifier = Modifier,
    usernameText: MutableState<String>,
    passwordText: MutableState<String>,
    onClickLogin: () -> Unit = { },
    status: MutableState<Int> = mutableStateOf(0)
) {

    Scaffold(

        topBar = { TopAppBar(
            backgroundColor = MaterialTheme.colors.primarySurface,
            ) {
            Text(
                "Login",
                style = MaterialTheme.typography.subtitle2,
                modifier = modifier.padding(start = 10.dp)
            )
        }},

        floatingActionButton = {
            FloatingActionButton(onClick = { /*TODO*/ }) {
                Row(modifier = modifier.padding(8.dp)) {
                    Icon(Icons.Filled.AppRegistration, contentDescription = "Signup Icon")
                    Text("Sign up")
                }
            }
        }
    ) {
        Column(modifier = modifier.fillMaxSize()) {

            TextField(
                value = usernameText.value,
                label = { Text("Username") },
                onValueChange = { usernameText.value = it },
                shape = RoundedCornerShape(0),
                modifier = modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 150.dp)
            )



            TextField(
                value = passwordText.value,
                label = { Text("Password") },
                onValueChange = { passwordText.value = it },
                shape = RoundedCornerShape(0),
                modifier = modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 40.dp)
            )



            Button(
                onClick = { onClickLogin() },
                enabled = (!usernameText.value.isEmpty() && !passwordText.value.isEmpty()),
                modifier = modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 32.dp)
            ) {
                Text(
                    "Login",
                    modifier = Modifier.padding(
                        start = 16.dp,
                        end = 16.dp,
                        top = 4.dp,
                        bottom = 4.dp
                    )
                )
            }


            Text(
                "cur status is: ${status.value}",
                modifier = Modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 16.dp)
            )


        }
    }

}







@Composable
@Preview
fun LoginPreview() {
    val usernameText = remember { mutableStateOf("") }
    val passwordText = remember { mutableStateOf("") }
    TriviaAndroidTheme {
        LoginScreenContent(usernameText = usernameText, passwordText = passwordText)
    }
}