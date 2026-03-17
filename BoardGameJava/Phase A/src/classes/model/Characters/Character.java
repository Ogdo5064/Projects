package classes.model.Characters;

import classes.model.Board.Area;
import classes.model.Board.Board;
import classes.model.Player.Player;

import java.io.Serializable;
import java.util.EnumMap;
import java.util.List;

/**
 * Abstract class representing a character in the game.
 * Character -> archeologist-assistant-digger-professor
 * Each character has a unique special ability
 */
public abstract class Character implements Serializable {

    /**
     * Creates a 2D array of Character-Boolean type
     * @return 2D object array
     **/
    public static Object[][] characterBuilder() {
        // [5 rows][2 columns]
        Object[][] roster = new Object[5][2];

        roster[0][0] = new Coder();
        roster[0][1] = false;

        roster[1][0] = new Archeologist();
        roster[1][1] = false;

        roster[2][0] = new Professor();
        roster[2][1] = false;

        roster[3][0] = new Assistant();
        roster[3][1] = false;

        roster[4][0] = new Digger();
        roster[4][1] = false;

        return roster;
    }

    /**
     * Executes the character's special ability.
     */
    public abstract EnumMap<Area, Integer> ability(Board board, Player player, Area forbiddenArea);
}
