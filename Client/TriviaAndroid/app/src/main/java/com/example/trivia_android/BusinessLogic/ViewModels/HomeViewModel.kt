package com.example.trivia_android.BusinessLogic.ViewModels

import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import com.example.trivia_android.BusinessLogic.Communications.Communications


class HomeViewModel: ViewModel() {

    var curScreen by mutableStateOf("Home")
    val comms = Communications

}