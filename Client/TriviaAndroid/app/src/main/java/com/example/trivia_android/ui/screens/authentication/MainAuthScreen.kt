package com.example.trivia_android.ui.screens.authentication

import android.util.Log
import androidx.compose.runtime.Composable
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.trivia_android.BusinessLogic.ViewModels.LoginViewModel




/*
Main Auth Screen is responsible for handling the authentication UI.
Thus it serves as a wrapper function to pack both login and signup and the navigation between them.
*/
@Composable
fun MainAuthScreen(loginViewModel: LoginViewModel = viewModel(), onLogin: () -> Unit = {  }) {
    val navController = rememberNavController()

    NavHost(
        navController = navController,
        // sets the starting screen as the Login screen
        startDestination = "Login",
    ) {


        composable("Login") {
            LoginScreenContent(
                usernameText = loginViewModel.username,
                passwordText = loginViewModel.password,
                onClickLogin = { loginViewModel.login() },
                onClickSwitch = { navController.navigate("Signup") },
                onSuccessLogin = { onLogin() },
                status = loginViewModel.successStatus
            )
        }


        composable("Signup") {
            SignupScreenContent(
                usernameText = loginViewModel.username,
                passwordText = loginViewModel.password,
                emailText = loginViewModel.email,
                onClickSignup = { loginViewModel.signup() },
                onClickSwitch = { navController.navigate("Login") },
                onSuccessSignup = { onLogin() },
                status = loginViewModel.successStatus
            )
        }


    }

}