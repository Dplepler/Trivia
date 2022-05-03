package com.example.trivia_android.BusinessLogic.ViewModels


import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.trivia_android.BusinessLogic.Communications.Communications
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json


@Serializable
data class Status(val status: Int)
@Serializable
data class LoginData(val username: String, val password: String)
@Serializable
data class SignupData(val username: String, val password: String, val mail: String)



class LoginViewModel: ViewModel() {

    val comms: Communications = Communications
    var successStatus = mutableStateOf(-3)
    val username = mutableStateOf("")
    val password = mutableStateOf("")
    val email = mutableStateOf("")


    init {
        viewModelScope.launch {
            comms.connectSocket()
        }
    }



    fun login() {
        viewModelScope.launch {
            val data = Json.encodeToString(LoginData(username.value, password.value))
            comms.sendMessage(comms.buildMessage(12, data))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == 22) {
                val res = String(buffer).substring(5)
                successStatus.value = Json.decodeFromString<Status>(res).status
            }
        }
    }



    fun signup() {
        viewModelScope.launch {
            val data = Json.encodeToString(SignupData(username.value, password.value, email.value))
            comms.sendMessage(comms.buildMessage(11, data))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == 21) {
                val res = String(buffer).substring(5)
                successStatus.value = Json.decodeFromString<Status>(res).status
            }
        }
    }




}