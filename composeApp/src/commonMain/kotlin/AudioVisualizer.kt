import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material.Card
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import org.jetbrains.compose.resources.ExperimentalResourceApi

@OptIn(ExperimentalResourceApi::class)
@Composable
fun audioVisualizerView(modifier: Modifier = Modifier) {
    Card(
        backgroundColor = Color.DarkGray,
        modifier = modifier.padding(horizontal = 16.dp, vertical = 32.dp).fillMaxWidth()
    ) {
        Text(
            text = "AudioVisualizer",
        )
    }

}
