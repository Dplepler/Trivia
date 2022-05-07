package com.example.trivia_android

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material.Button
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.trivia_android.BusinessLogic.ViewModels.LoginViewModel
import com.example.trivia_android.ui.screens.authentication.LoginScreenContent
import com.example.trivia_android.ui.screens.authentication.MainAuthScreen
import com.example.trivia_android.ui.screens.home.MainMenu
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import com.google.accompanist.navigation.animation.AnimatedNavHost

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            TriviaAndroidTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colors.background
                ) {
                    val mainNavController = rememberNavController()
                    NavHost(navController = mainNavController, startDestination = "Auth") {
                        composable("Auth") {
                            MainAuthScreen(onLogin = { mainNavController.navigate("MainMenu") })
                        }

                        composable("MainMenu") {
                            MainMenu()
                        }

                    }
                }
            }
        }
    }
}