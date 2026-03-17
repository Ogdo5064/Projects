package classes.model.Characters;

import classes.model.Board.Area;
import classes.model.Board.Board;
import classes.model.Player.Player;

import java.io.Serializable;
import java.util.EnumMap;

/**
 * Represents the professor character
 */
public class Professor extends Character implements Serializable {

    @Override
    public EnumMap<Area, Integer> ability(Board board, Player player, Area forbiddenArea){
        EnumMap<Area,Integer> map = new EnumMap<>(Area.class);
        map.put(Area.ANY,3);
        map.put(forbiddenArea,0);

        return map;
    }

}
