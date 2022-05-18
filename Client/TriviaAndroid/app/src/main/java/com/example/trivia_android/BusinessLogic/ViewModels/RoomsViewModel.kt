package com.example.trivia_android.BusinessLogic.ViewModels

import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import com.example.trivia_android.BusinessLogic.Communications.Communications


class RoomsViewModel: ViewModel() {

    val comms = Communications

    val playerAmount = mutableStateOf("")

    val ansTime = mutableStateOf("")

    val roomName = mutableStateOf("")


    fun createRoom() {

    }


}