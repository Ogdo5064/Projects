package classes.model.Characters;

import classes.model.Board.Area;
import classes.model.Board.Board;
import classes.model.Player.Player;

import java.io.Serializable;
import java.util.EnumMap;

/**
 * Represents the digger character
 */
public class Digger extends Character implements Serializable {

    @Override
    public EnumMap<Area, Integer> ability(Board board, Player player, Area forbiddenArea){
        EnumMap<Area,Integer> map = new EnumMap<>(Area.class);
        map.put(forbiddenArea,2);
        return map;
    }

}
