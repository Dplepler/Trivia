package com.example.trivia_android.ui.screens.Rooms

import android.util.Log
import android.widget.Toast
import androidx.compose.animation.AnimatedVisibility
import androidx.compose.animation.ExperimentalAnimationApi
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.ArrowDropDown
import androidx.compose.material.icons.filled.ArrowDropUp
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.layout.onGloballyPositioned
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.toSize
import com.example.trivia_android.ui.SharedComponents.SharpTextField
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun InfoDropDown(
    modifier: Modifier = Modifier,
    label: String,
    chosenValue: MutableState<String>,
    options: List<Int>
) {

    var expanded by remember { mutableStateOf(false) }

    var textfieldSize by remember { mutableStateOf(Size.Zero)}


    val icon = if (expanded)
        Icons.Filled.ArrowDropUp
    else
        Icons.Filled.ArrowDropDown


    Column(modifier) {
        OutlinedTextField(
            modifier = modifier
                .width(130.dp)
                .onGloballyPositioned { coordinates ->
                    textfieldSize = coordinates.size.toSize()
                },
            shape = RoundedCornerShape(8.dp),
            value = chosenValue.value,
            onValueChange = { chosenValue.value = it },
            label = { Text(label) },
            trailingIcon = {
                Icon(icon,"contentDescription",
                    Modifier.clickable { expanded = !expanded })
            }
        )

        DropdownMenu(
            expanded = expanded,
            onDismissRequest = { expanded = false },
            modifier = Modifier
                .width(with(LocalDensity.current) { textfieldSize.width.toDp() })
        ) {
            options.forEach { option ->
                DropdownMenuItem(onClick = {
                    chosenValue.value = option.toString()
                    expanded = false
                }) {
                    Text(option.toString())
                }
            }
        }
    }
}




@OptIn(ExperimentalAnimationApi::class)
@Composable
fun CreateRoom(
    modifier: Modifier = Modifier,
    roomName: MutableState<String>,
    playerVal: MutableState<String>,
    ansTimeVal: MutableState<String>,
    onClickSubmit: () -> Unit = { },
    onSuccessCreate: () -> Unit = { },
) {

    val enabled = !roomName.value.isEmpty() && !playerVal.value.isEmpty() && !ansTimeVal.value.isEmpty()
    val curContext = LocalContext.current


    Scaffold(
        topBar = { TopAppBar(
            backgroundColor = MaterialTheme.colors.primarySurface,
            modifier = modifier.clip(RoundedCornerShape(bottomStart = 4.dp, bottomEnd = 4.dp))
        ) {
            Text("Create a room!", style = MaterialTheme.typography.subtitle2)
        } },
        
        floatingActionButton = {
            FloatingActionButton(
                onClick = {
                    if(enabled) { onClickSubmit() }
                    else
                    { Toast.makeText(curContext, "enter room info!", Toast.LENGTH_LONG).show() } },
                backgroundColor = MaterialTheme.colors.primary
            ) {

                Row(modifier = Modifier.padding(8.dp)) {
                    Icon(Icons.Filled.Add, null)

                    AnimatedVisibility(visible = enabled) {
                        Text(
                            "Create",
                            modifier = Modifier.align(Alignment.CenterVertically)
                        )
                    }
                }

            }
        }
        
    ) {

        Column {

            Text(
                "Room Name: ",
                style = MaterialTheme.typography.caption,
                modifier = Modifier.padding(top = 28.dp, bottom = 4.dp)
            )

            SharpTextField(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(bottom = 16.dp),
                stringState = roomName,
                label = "Name"
            )


            Text(
                "Room Info: ",
                style = MaterialTheme.typography.caption,
                modifier = Modifier
                    .align(Alignment.CenterHorizontally)
                    .padding(top = 16.dp, bottom = 4.dp)
            )

            Row(modifier = Modifier.align(Alignment.CenterHorizontally)) {

                InfoDropDown(
                    modifier = Modifier.padding(end = 8.dp),
                    label = "Players",
                    chosenValue = playerVal,
                    options = (1..30).toList()
                )


                InfoDropDown(
                    modifier = Modifier,
                    label = "Time",
                    chosenValue = ansTimeVal,
                    options = (10..180 step(10)).toList()
                )
            }

        }

    }
}








@Composable
@Preview
fun InfoPreview() {

    val value = remember { mutableStateOf("") }
    val value2 = remember { mutableStateOf("")}

    TriviaAndroidTheme {

        Row {

            InfoDropDown(
                modifier = Modifier.padding(end = 8.dp),
                label = "Players",
                chosenValue = value,
                options = (1..30).toList()
            )


            InfoDropDown(
                modifier = Modifier,
                label = "Time",
                chosenValue = value2,
                options = (10..180 step(10)).toList()
            )

        }

    }

}


@Composable
@Preview
fun CreateScreenPreview() {

    val sugoma = remember { mutableStateOf("") }
    val sugoma2 = remember { mutableStateOf("") }
    val sugoma3 = remember { mutableStateOf("") }

    TriviaAndroidTheme {
        CreateRoom(
            roomName = sugoma,
            playerVal = sugoma2,
            ansTimeVal = sugoma3,
            onClickSubmit = { Log.i("Create:", "Button Clicked") }
        )
    }
}
