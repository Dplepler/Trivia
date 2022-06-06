package com.example.trivia_android.ui.SharedComponents

import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.PasswordVisualTransformation
import androidx.compose.ui.text.input.VisualTransformation
import androidx.compose.ui.unit.dp



// General text field composable
@Composable
fun SharpTextField(
    modifier: Modifier = Modifier,
    stringState: MutableState<String>,
    color: Color = MaterialTheme.colors.primary,
    label: String,
    isPassword: Boolean = false
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
        keyboardOptions = KeyboardOptions(keyboardType = if(isPassword) KeyboardType.Password else KeyboardType.Text),
        visualTransformation = if(isPassword) PasswordVisualTransformation() else VisualTransformation.None,
        modifier = modifier
    )
}