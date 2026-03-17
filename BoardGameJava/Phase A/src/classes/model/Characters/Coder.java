package classes.model.Characters;

import classes.model.Board.Area;
import classes.model.Board.Board;
import classes.model.Player.Player;

import java.io.Serializable;
import java.util.EnumMap;

/**
 * Represents the Coder character
 */
public class Coder extends Character implements Serializable {

    public EnumMap<Area, Integer> ability(Board board, Player player, Area forbiddenArea) {
        EnumMap<Area, Integer> map = new EnumMap<>(Area.class);

        // secret code , if any=0 then we go to area choosing mode
        map.put(Area.ANY, 0);

        return map;
    }

}
