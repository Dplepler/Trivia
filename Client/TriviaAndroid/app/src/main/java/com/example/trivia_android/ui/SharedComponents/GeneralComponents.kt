package com.example.trivia_android.ui.SharedComponents

import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp



// General text field composable
@Composable
fun SharpTextField(
    modifier: Modifier = Modifier,
    stringState: MutableState<String>,
    color: Color = MaterialTheme.colors.primary,
    label: String
) {
    TextField(
        value = stringState.value,
        label = { Text(label) },
        onValueChange = { stringState.value = it },
        shape = RoundedCornerShape(0),
        colors = TextFieldDefaults.textFieldColors(
            focusedLabelColor = color,
            focusedIndicatorColor = color,
            cursorColor = color
        ),
        modifier = modifier
    )
}