package com.example.trivia_android.ui.SharedComponents

import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.Text
import androidx.compose.material.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp


@Composable
fun SharpTextField(
    modifier: Modifier = Modifier,
    stringState: MutableState<String>,
    label: String
) {
    TextField(
        value = stringState.value,
        label = { Text(label) },
        onValueChange = { stringState.value = it },
        shape = RoundedCornerShape(0),
        modifier = modifier
    )
}