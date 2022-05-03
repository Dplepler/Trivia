package com.example.trivia_android.ui.screens.authentication

import androidx.compose.runtime.Composable
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.trivia_android.BusinessLogic.ViewModels.LoginViewModel


@Composable
fun MainAuthScreen(loginViewModel: LoginViewModel = viewModel()) {
    val navController = rememberNavController()

    NavHost(
        navController = navController,
        startDestination = "Login",
    ) {


        composable("Login") {
            LoginScreenContent(
                usernameText = loginViewModel.username,
                passwordText = loginViewModel.password,
                onClickLogin = { loginViewModel.login() },
                onClickSwitch = { navController.navigate("Signup") },
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
                status = loginViewModel.successStatus
            )
        }


    }

}