package com.example.trivia_android.ui.theme

import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.material.MaterialTheme
import androidx.compose.material.darkColors
import androidx.compose.material.lightColors
import androidx.compose.runtime.Composable
import androidx.compose.ui.graphics.Color

private val DarkColorPalette = darkColors(
    primary = Marine500,
    primaryVariant = Marine200,
    secondary = Blue200,
    secondaryVariant = Blue500,
    onPrimary = Color.White
)

private val LightColorPalette = lightColors(
    primary = Blue200,
    primaryVariant = Blue500,
    onPrimary = Color.Black,
    secondary = Marine500,
    secondaryVariant = Marine200,
    onSecondary = Color.White,

    /* Other default colors to override
    background = Color.White,
    surface = Color.White,
    onSecondary = Color.Black,
    onBackground = Color.Black,
    onSurface = Color.Black,
    */
)

@Composable
fun TriviaAndroidTheme(
    darkTheme: Boolean = isSystemInDarkTheme(),
    content: @Composable () -> Unit
) {
    val colors = if (darkTheme) {
        DarkColorPalette
    } else {
        LightColorPalette
    }

    MaterialTheme(
        colors = colors,
        typography = Typography,
        shapes = Shapes,
        content = content
    )
}