package classes.Controller;

import javax.sound.sampled.*;
import java.io.File;

public class SoundManager {

    private Clip currentClip; // keep track of what is playing so we can stop it

    /**
     * Stops specific previous music and starts the new player's theme
     */
    public void playPlayerTheme(int playerIndex) {
        String filename = "src/assets/music/Player" + (playerIndex + 1) + ".wav";

        playMusic(filename);
    }

    public void playMusic(String filepath) {
        try {
            stopMusic();
            File musicPath = new File(filepath);
            if (musicPath.exists()) {
                AudioInputStream audioInput = AudioSystem.getAudioInputStream(musicPath);
                currentClip = AudioSystem.getClip();
                currentClip.open(audioInput);

                // Lower the volume
                FloatControl gainControl = (FloatControl) currentClip.getControl(FloatControl.Type.MASTER_GAIN);
                gainControl.setValue(-10.0f);

                currentClip.start();
                currentClip.loop(Clip.LOOP_CONTINUOUSLY);
            } else {
                System.out.println("Music file not found: " + filepath);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Stops the music
     */
    public void stopMusic() {
        if (currentClip != null && currentClip.isRunning()) {
            currentClip.stop();
            currentClip.close(); // Important to release memory
        }
    }
}