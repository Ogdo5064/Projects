package classes.model.Player;

import classes.model.Board.Area;
import classes.model.Characters.*;
import classes.model.Characters.Character;
import classes.model.Tiles.*;
import classes.model.Board.*;

import java.io.Serializable;
import java.util.*;


/**
 * Represents a player in the game.
 * Each player has a name, a chosen character type, a personal backpack
 * for storing collected tiles, and a flag indicating whether the character's
 * ability has been used this turn.
 *
 * @author Dimokritos Bompos
 * @version 1.0
 */
public class Player implements Serializable {

    /** The player's display name.*/
    private String name;

    /** List of tiles collected by the player. */
    private List<Tile> backpack;

    private Area coderBonusArea = null;

    private Object[][] characters;
    /**
     * Creates a new player with a name and assigned characters
     */
    public Player(String name) {
        this.name = name;
        this.backpack = new LinkedList<>();
        this.characters = Character.characterBuilder();
    }

    /**
     * Getter for characters
     * @return array of characters
     */
    public Object[][] getCharacters() {
        return this.characters;
    }


    /** Returns the player's name. */
    public String getName() { return name; }

    /** Returns the list of tiles collected by the player. */
    public List<Tile> getBackpack() { return backpack; }

    /**
     * Adds a tile to the player's backpack.
     *
     * @param tile the tile to add
     */
    public void addTile(Tile tile) { backpack.add(tile); }

    /**
     * Returns the player's total score.
     * No statue calculation here
     * @return the player's point total
     */
    public int countPoints(Player player) {
        List<Tile> backpack = player.getBackpack();
        int points=0;
        int mosaicCounter=0;
        int bigUpper=0,bigLower=0,smallUpper=0,smallLower=0;

        EnumMap<classes.model.Tiles.Color, Integer> mosaicCalc = new EnumMap<>(classes.model.Tiles.Color.class);
        for (classes.model.Tiles.Color c : classes.model.Tiles.Color.values()) {
            mosaicCalc.put(c, 0);
        }

        Set<Color> distinctAmphoraColors = new java.util.HashSet<>();

        for(Tile tile : backpack){
            //==========MOSAIC COUNTING==========//
            if(tile instanceof MosaicTile){
                mosaicCounter++;
                mosaicCalc.put(((MosaicTile) tile).getColor(),mosaicCalc.get(((MosaicTile) tile).getColor())+1);
            }
            //==========SKELETON COUNTING==========//
            if(tile instanceof SkeletonTile){
                SkeletonType type = ((SkeletonTile) tile).getType();
                switch (type) {
                    case BIG_UPPER: bigUpper++; break;
                    case BIG_LOWER: bigLower++; break;
                    case SMALL_UPPER: smallUpper++; break;
                    case SMALL_LOWER: smallLower++; break;
                }
            }
            if(tile instanceof AmphoraTile){
                classes.model.Tiles.Color c = ((AmphoraTile) tile).getColor();
                distinctAmphoraColors.add(c);
                //add on a set ignores duplicates
            }
        }

        //==========MOSAIC CALCULATION==========//

        //mosaics can be green red yellow
        //if 4 mosaics are the same color you get 4 points
        //if 4 mosaics are at least from 2 different colors you get 2 points
        //if not 4 mosaics you get 0 points
        int green = mosaicCalc.get(Color.GREEN)/4;
        int red = mosaicCalc.get(Color.RED)/4;
        int yellow = mosaicCalc.get(Color.YELLOW)/4;
        points+= green*4 + yellow*4 + red*4;

        //leftovers

        int greenLeftover = mosaicCalc.get(Color.GREEN)%4;
        int redLeftover = mosaicCalc.get(Color.RED)%4;
        int yellowLeftover = mosaicCalc.get(Color.YELLOW)%4;

        int mixedSets = (greenLeftover + redLeftover + yellowLeftover)/4;
        points+= mixedSets*2;

        //==========SKELETON CALCULATION==========//

        int fullBigSkeletons = Math.min(bigLower, bigUpper);
        int fullSmallSkeletons = Math.min(smallLower, smallUpper);

        int families = Math.min(fullBigSkeletons / 2, fullSmallSkeletons);

        points += families * 6;

        int remainingBigs = fullBigSkeletons - (families * 2);
        int remainingSmalls = fullSmallSkeletons - (families);

        points += remainingBigs + remainingSmalls;

        //==========AMPHORA CALCULATION==========//

        points += distinctAmphoraColors.size();


        return points;
    }


    public void setCoderBonusArea(Area area) {this.coderBonusArea = area;}

    public Area getCoderBonusArea() {return this.coderBonusArea;}

    public void clearCoderBonus() {this.coderBonusArea = null;}
}
