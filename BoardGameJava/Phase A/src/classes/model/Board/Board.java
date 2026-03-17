package classes.model.Board;

import classes.model.Player.Player;
import classes.model.Tiles.*;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.EnumMap;
import java.util.Stack;
import java.util.Collections;

/**
 * Represents the board on which the game will be played.
 * Contains 4 tile areas and 1 bag area.
 *
 * @author Dimokritos Bompos
 * @version 1.0
 */
public class Board implements Serializable {

    /**
     * Hashtable (EnumMap) containing the 4 board areas.
     * Key is an enum value of Area, value is a list of Tile objects.
     */
    private EnumMap<Area, List<Tile>> areas;

    /**
     * The main bag of the game, implemented as a stack of Tile objects.
     */
    private Stack<Tile> mainBag;

    /**
     * A list containing all players of the game.
     */
    private ArrayList<Player> players;

    /**
     * Index of the player whose turn it currently is.
     */
    private int currentPlayerIndex;

    /**
     * Board constructor initializing the areas, bag, and player list.
     */
    public Board(int num) {

        mainBag = new Stack<>();
        areas = new EnumMap<>(Area.class);
        currentPlayerIndex = 0;

        for (Area area : Area.values()) {
            areas.put(area, new ArrayList<>());
        }

        Tile tmpTile;


        // Mosaics
        Color tmpTileColor = Color.RED;
        for (int i = 0; i < 27; i++) {
            if (i == 9) tmpTileColor = Color.GREEN;
            if (i == 18) tmpTileColor = Color.YELLOW;
            tmpTile = new MosaicTile(tmpTileColor, -1);
            this.addToBag(tmpTile);
        }

        // Statues
        for (int i = 0; i < 24; i++) {
            if (i < 12) tmpTile = new CaryatidTile(-1);
            else tmpTile = new SphinxTile(-1);
            this.addToBag(tmpTile);
        }

        // Amphora
        Color[] allColors = Color.values();
        for (int i = 0; i < 30; i++) {
            int colorIndex = (i / 5) % allColors.length;
            tmpTileColor = allColors[colorIndex];
            tmpTile = new AmphoraTile(tmpTileColor, -1);
            this.addToBag(tmpTile);
        }

        // Landslides
        for (int i = 0; i < 24; i++) {
            tmpTile = new LandslideTile(-1);
            addToBag(tmpTile);
        }

        // Skeletons
        for (int i = 0; i < 30; i++) {
            if (i < 10) tmpTile = new SkeletonTile(SkeletonType.BIG_UPPER, -1);
            else if (i < 20) tmpTile = new SkeletonTile(SkeletonType.BIG_LOWER, -1);
            else if (i < 25) tmpTile = new SkeletonTile(SkeletonType.SMALL_UPPER, -1);
            else tmpTile = new SkeletonTile(SkeletonType.SMALL_LOWER, -1);
            addToBag(tmpTile);
        }

        Collections.shuffle(mainBag);

        players = new ArrayList<>();
        for (int i = 1; i < num+1; i++) {
            players.add(new Player("Player" + i));
        }
        if (num == 1) {
            players.add(new Player("Thief"));
        }
    }

    /**
     * Getter for players
     * @return returns a list
     */
    public ArrayList<Player> getPlayers(){
        return this.players;
    }

    /**
     * Getter for areas
     * @return returns EnumMap
     */
    public EnumMap<Area, List<Tile>> getAreas(){
        return areas;
    }

    /**
     * Adds a Tile object into the bag (stack).
     *
     * @param obj the Tile object to be added
     */
    public void addToBag(Tile obj) {
        mainBag.push(obj);
    }

    /**
     * Removes and returns one Tile object from the bag (stack).
     *
     * @return the Tile drawn from the top of the bag
     */
    public Tile drawTile() {
        if(mainBag.empty()) {
            return null;
        }
        return mainBag.pop();
    }

    /**
     * Distributes the tile in the correct area according to it's instance
     * @param tile to seach instance
     */
    public void distributeTile(Tile tile){
        if(tile == null)return;

        Area targetArea=null;

        if(tile instanceof AmphoraTile){
            targetArea = Area.AMPHORA;
        }
        else if(tile instanceof MosaicTile){
            targetArea = Area.MOSAIC;
        }
        else if(tile instanceof SkeletonTile){
            targetArea = Area.SKELETON;
        }
        else if(tile instanceof StatueTile){
            targetArea = Area.SKELETON;
        }
        else if(tile instanceof LandslideTile){
            targetArea = Area.ENTRANCE;
        }

        if(targetArea!= null){
            addObject(targetArea,tile);
        }
    }

    /**
     * Returns the main bag as a stack.
     *
     * @return the stack of Tile objects representing the bag
     */
    public Stack<Tile> getMainBag() {
        return mainBag;
    }

    /**
     * Returns the tile's area
     */
    public Area getTileArea(Tile tile) {
        if (tile == null) return null;

        Area targetArea = null;

        if (tile instanceof AmphoraTile) {
            targetArea = Area.AMPHORA;
        } else if (tile instanceof MosaicTile) {
            targetArea = Area.MOSAIC;
        } else if (tile instanceof SkeletonTile) {
            targetArea = Area.SKELETON;
        } else if (tile instanceof StatueTile) {
            targetArea = Area.STATUE;
        } else if (tile instanceof LandslideTile) {
            targetArea = Area.ENTRANCE;
        }

        return targetArea;
    }


    /**
     * Returns the player whose turn it currently is.
     *
     * @return the current Player object
     */
    public Player getCurrentPlayer() {
        return players.get(currentPlayerIndex);
    }

    /**
     * Getter for currentPlayerIndex
     * @return the current player int number
     */
    public int getCurrentPlayerIndex(){
        return this.currentPlayerIndex;
    }

    /**
     * Advances the turn to the next player.
     * Uses modular arithmetic to loop back to the first player.
     */
    public void assignNextPlayerTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }


    /**
     * Returns the winning player of the game.
     *
     * @return the Player who won
     */
    public Player getWinner() {
        List<Player> players = this.getPlayers();
        int[] points = new int[4];
        int i=0;
        Player winner = getPlayers().get(0);
        //Calculates points without statues
        for(Player player : getPlayers()){
            points[i] = player.countPoints(player);
            i++;
        }
        //Calculates points for statues only
        points = calculateStatuePoints(points);

        int maxScore = -1;

        for(i = 0; i < getPlayers().size(); i++){
            System.out.println("Player " + (i+1) + " Points: " + points[i]);

            if(points[i] > maxScore){
                maxScore = points[i];
                winner = getPlayers().get(i);
            }
        }
        return winner;
    }

    /**
     * Calculates the statue points only and adds them to the overall points
     */
    public int[] calculateStatuePoints(int[] points) {
        int numPlayers = getPlayers().size();

        int[] sphinxCounts = new int[numPlayers];
        int[] caryatidCounts = new int[numPlayers];

        for (int i = 0; i < numPlayers; i++) {
            Player player = getPlayers().get(i);
            List<Tile> backpack = player.getBackpack();

            int sCount = 0;
            int cCount = 0;

            for (Tile tile : backpack) {
                if (tile instanceof SphinxTile) sCount++;
                else if (tile instanceof CaryatidTile) cCount++;
            }

            sphinxCounts[i] = sCount;
            caryatidCounts[i] = cCount;
        }

        applyStatueRules(sphinxCounts, points);
        applyStatueRules(caryatidCounts, points);

        return points;
    }

    /**
     * Helper for statue points calculations
     */
    private void applyStatueRules(int[] counts, int[] totalPoints) {
        int max = -1;
        int min = Integer.MAX_VALUE;

        for (int count : counts) {
            if (count > max) max = count;
            if (count < min) min = count;
        }

        for (int i = 0; i < counts.length; i++) {
            if (counts[i] == max) {
                totalPoints[i] += 6;
            }
            else if (counts[i] == min) {
                totalPoints[i] += 0;
            }
            else {
                totalPoints[i] += 2;
            }
        }
    }

    /**
     * Applies the landslide effect on the board.
     */
    public void applyLandslide() {
        System.out.println(this.getWinner().getName()+" won the game!");
        System.exit(1);
    }

    /**
     * Adds a Tile into the specified area.
     *
     * @param area the area into which the tile will be added
     * @param obj the Tile to be added
     */
    public void addObject(Area area, Tile obj) {
        areas.get(area).add(obj);
    }

    /**
     * Removes the tile from the area
     */
    public void removeObject(Area area, Tile t) {
        List<Tile> list = areas.get(area);
        if(list != null) {
            list.remove(t);
        }
    }
}
