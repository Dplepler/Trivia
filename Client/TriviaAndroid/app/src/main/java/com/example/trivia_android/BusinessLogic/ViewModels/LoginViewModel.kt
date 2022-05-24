package com.example.trivia_android.BusinessLogic.ViewModels


import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.trivia_android.BusinessLogic.Communications.Communications
import com.example.trivia_android.BusinessLogic.Communications.RequestCodes
import com.example.trivia_android.BusinessLogic.Communications.ResponseCodes
import com.example.trivia_android.BusinessLogic.Communications.Status
import com.example.trivia_android.BusinessLogic.Communications.UserInfo
import kotlinx.coroutines.launch
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json


@Serializable
data class LoginData(val username: String, val password: String)
@Serializable
data class SignupData(val username: String, val password: String, val mail: String)



class LoginViewModel: ViewModel() {

    val comms: Communications = Communications
    private val userInfo = UserInfo
    var successStatus = mutableStateOf(0)
    val username = mutableStateOf("")
    val password = mutableStateOf("")
    val email = mutableStateOf("")


    init {
        viewModelScope.launch {
            comms.connectSocket()
        }
    }



    fun login() {
        userInfo.userName = username.value
        userInfo.password = password.value
        viewModelScope.launch {
            val data = Json.encodeToString(LoginData(username.value, password.value))
            comms.sendMessage(comms.buildMessage(RequestCodes.Login.code.toByte(), data))
            val buffer = comms.readMessage()
            // checks that the response is relevant and not an error
            if(buffer[0].toInt() == ResponseCodes.Login.code) {
                val res = String(buffer).substring(comms.headerLen)
                successStatus.value = Json.decodeFromString<Status>(res).status
            }
        }
        clearTexts()
    }



    fun signup() {
        userInfo.userName = username.value
        userInfo.password = password.value
        viewModelScope.launch {
            val data = Json.encodeToString(SignupData(username.value, password.value, email.value))
            comms.sendMessage(comms.buildMessage(RequestCodes.Signup.code.toByte(), data))
            val buffer = comms.readMessage()
            // checks that the response is relevant and not an error
            if(buffer[0].toInt() == ResponseCodes.Signup.code) {
                val res = String(buffer).substring(comms.headerLen)
                successStatus.value = Json.decodeFromString<Status>(res).status
            }
        }
        clearTexts()
    }


    // clears text after login/signup to make it easier to reenter a username or a password
    private fun clearTexts() {
        username.value = ""
        password.value = ""
        email.value = ""
    }



}