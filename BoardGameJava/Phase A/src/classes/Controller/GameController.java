package classes.Controller;

import classes.View.Viewer;
import classes.model.Board.Area;
import classes.model.Board.Board;
import classes.model.Characters.Character;
import classes.model.Player.Player;
import classes.model.Tiles.*;
import java.util.List;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.EnumMap;
import java.util.Map;

public class GameController {

    private static Board board;
    private static Viewer view;

    //GAME STATE
    private static int tilesDrawnCounter = 0;
    private static int tilesChosen = 0;
    private static Area chosenAreaForCollection = null;

    //ABILITY STATE
    private static boolean isAbilityUsed = false;
    private static EnumMap<Area, Integer> activeAbilityMap = null;
    private static int activeCharacterIndex = -1;

    //TIMER VARIABLES
    private static Timer turnTimer;
    private static int timeLeft = 30;

    //MUSIC VARIABLES
    private static SoundManager soundManager;

    /**
     * Main flow of the game
     * Initializes all required objects for the game
     */
    public static void main(String[] args) {

        int userInput=-1;
        boolean validInput=false;

        while (!validInput) {
            String input = JOptionPane.showInputDialog(null, "1 or 4 players available:");

            // null means user clicked cancel
            if (input == null) {
                System.exit(0);
            }

            try {
                userInput = Integer.parseInt(input);
                if(userInput == 1 || userInput == 4){
                    validInput = true;
                }

            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(null, "Invalid input");
            }
        }

        board = new Board(userInput);
        soundManager = new SoundManager();
        view = new Viewer();
        view.initializeUI(board.getPlayers());
        //System.out.println(board.getPlayers().get(0).getName()+" and "+board.getPlayers().get(1).getName());
        view.updateVisiblePlayers(board.getPlayers().size());
        setupListeners();

        //INITIALIZE THE TIMER
        turnTimer = new Timer(1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                timeLeft--;
                view.updateTimerDisplay(timeLeft);

                if (timeLeft <= 0) {
                    ((Timer)e.getSource()).stop();
                    System.out.println("TIME IS UP! Turn Lost");

                    //force next turn
                    board.assignNextPlayerTurn();
                    startTurn();
                }
            }
        });

        //character Setup
        String[] charImagePaths = {
                "src/assets/images/coder.PNG",
                "src/assets/images/archaeologist.png",
                "src/assets/images/professor.png",
                "src/assets/images/assistant.png",
                "src/assets/images/digger.png"
        };

        for (int pIndex = 0; pIndex < board.getPlayers().size(); pIndex++) {
            int currentPlayer = pIndex;
            for (int cIndex = 0; cIndex < 5; cIndex++) {
                view.setCharacterIcon(currentPlayer, cIndex, charImagePaths[cIndex]);

                int characterType = cIndex;
                view.addCharacterButtonListener(currentPlayer, cIndex, e -> {
                    //check if it is your turn
                    if(board.getCurrentPlayerIndex() != currentPlayer){
                        System.out.println("Not your turn");
                        return;
                    }
                    //check if another ability is active
                    if (activeAbilityMap != null && !isMapEmpty(activeAbilityMap)) {
                        System.out.println("Finish your current ability first!");
                        return;
                    }
                    //check usage flags
                    if(isAbilityUsed){
                        System.out.println("Ability already used");
                        return;
                    }
                    if (tilesChosen < 2) {
                        System.out.println("You must choose your 2 mandatory tiles first!");
                        return;
                    }
                    boolean alreadyUsedCharacter = (boolean) board.getCurrentPlayer().getCharacters()[characterType][1];
                    if(alreadyUsedCharacter){
                        System.out.println("This character has already been used");
                        return;
                    }

                    //activate ability
                    System.out.println("Player " + (currentPlayer + 1) + " activates character " + characterType);
                    Character selectedChar = (Character) board.getCurrentPlayer().getCharacters()[characterType][0];

                    activeAbilityMap = selectedChar.ability(board, board.getCurrentPlayer(), chosenAreaForCollection);
                    activeCharacterIndex = characterType;

                    if (activeAbilityMap != null) {
                        //coder returns any 0 , which is secret code , not empty enumMap
                        System.out.println("Ability Active! Fulfilling requirements...");
                        view.setNextTurnButtonEnabled(true);
                    } else {
                        // Automatic abilities
                        board.getCurrentPlayer().getCharacters()[characterType][1] = true;
                        isAbilityUsed = true;
                        activeCharacterIndex = -1;
                        view.updateBagCount(board.getMainBag().size());
                    }
                });
            }

            view.addBackpackButtonListeners(currentPlayer, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent actionEvent) {
                    Player p = board.getPlayers().get(currentPlayer);
                    view.showBackpackDialog(p.getName(), p.getBackpack());
                }
            });

            view.addPlayerButtonListener(currentPlayer, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    view.toggleCharacterRow(currentPlayer);
                }
            });
        }

        startTurn();
    }

    /**
     * At the start of each turn these initializations and checks are mandatory
     */
    public static void startTurn() {
        //RESET TURN STATE
        tilesDrawnCounter = 0;
        tilesChosen = 0;
        isAbilityUsed = false;
        chosenAreaForCollection = null;
        activeAbilityMap = null;
        activeCharacterIndex = -1;

        //CHECK LANDSLIDE
        if (board.getAreas().get(Area.ENTRANCE).size() >= 16) {
            board.applyLandslide();
        }


        //HIGHLIGHT PLAYER
        int currentIndex = board.getCurrentPlayerIndex();
        soundManager.playPlayerTheme(currentIndex);
        //System.out.println("current index: "+currentIndex);
        if(currentIndex == 1 && board.getPlayers().size() < 4){
            System.out.println("Thief's turn\nThief is stealing all tiles remaining on the board");
            thiefPlayStyle();
            return;
        }
        view.highlightPlayerTurn(currentIndex);
        //System.out.println("Turn Started for Player " + (board.getCurrentPlayerIndex()));

        //CHECK CODER BONUS
        Area bonusArea = board.getCurrentPlayer().getCoderBonusArea();
        if (bonusArea != null) {
            System.out.println("Coder Bonus Active! You get 2 extra tiles from " + bonusArea);
            activeAbilityMap = new EnumMap<>(Area.class);
            activeAbilityMap.put(bonusArea, 2);
            board.getCurrentPlayer().clearCoderBonus();
            view.setNextTurnButtonEnabled(true);
        } else {
            view.setDrawButtonEnabled(true);
            view.setNextTurnButtonEnabled(false);
        }

        //RESTART TIMER
        if (turnTimer.isRunning()) {
            turnTimer.stop();
        }
        timeLeft = 30; // reset to 30 seconds
        view.updateTimerDisplay(timeLeft); // reset label
        turnTimer.start();
    }

    /**
     * Method for executing thief's move
     */
    public static void thiefPlayStyle() {
        for (Area area : Area.values()) {
            List<Tile> originalList = board.getAreas().get(area);

            //iteration through safe copy but deletion from original list
            if (originalList != null && !originalList.isEmpty()) {

                List<Tile> safeCopy = new ArrayList<>(originalList);

                for (Tile tile : safeCopy) {
                    if (board.getTileArea(tile) == Area.ENTRANCE) {
                        continue;
                    }
                    performPick(tile);
                }
            }
        }
        System.out.println("Thief finished stealing. Next turn...");
        //System.out.println("BEFORE PLAYER INDEX IS:"+board.getCurrentPlayerIndex());
        board.assignNextPlayerTurn();
        //System.out.println("AFTER PLAYER INDEX IS:"+board.getCurrentPlayerIndex());

        startTurn();
    }

    /**
     * Set's up all the required listeners for every object that needs them
     * Also almost every listener has it's ActionEvent parameter overridden
     */
    public static void setupListeners() {


        view.updateBagCount(board.getMainBag().size());

        //SAVE LISTENER
        view.addSaveListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //pause game while saving
                turnTimer.stop();

                //call save logic
                saveGame();

                //resume timer
                turnTimer.start();
            }
        });

        //LOAD LISTENER
        view.addLoadListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // confirmation for load
                int confirm = JOptionPane.showConfirmDialog(null,
                        "Loading will overwrite your current game. Continue?",
                        "Load Game", JOptionPane.YES_NO_OPTION);

                if (confirm == JOptionPane.YES_OPTION) {
                    turnTimer.stop();

                    //call load logic
                    loadGame();

                    //restart timer
                    turnTimer.start();
                }
            }
        });

        // --- DRAW BUTTON --- //
        view.addDrawButtonListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                Tile drawnTile = board.drawTile();
                board.distributeTile(drawnTile);
                view.findWhereTileGoes(drawnTile);
                view.updateBagCount(board.getMainBag().size());
                tilesDrawnCounter++;

                if(board.getAreas().get(Area.ENTRANCE).size() >= 16){
                    System.out.println("A LANDSLIDE IS HAPPENING!");
                    board.applyLandslide();
                    // view.clearLandslideArea();
                    return;
                }
                if (tilesDrawnCounter >= 4) {
                    System.out.println("Mandatory draws complete.");
                    view.setDrawButtonEnabled(false);
                    view.setNextTurnButtonEnabled(true);
                }
            }
        });

        // --- NEXT TURN BUTTON --- //
        view.addNextTurnButtonListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(tilesChosen < 2){
                    System.out.println("You must choose 2 tiles before finishing");
                    return;
                }

                // stop timer when finishing turn by hand
                turnTimer.stop();

                System.out.println("Player finished their turn.");
                board.assignNextPlayerTurn();
                startTurn();
            }
        });

        // --- TILE CLICK LISTENER --- //
        view.setTileClickListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                JButton clickedBtn = (JButton) e.getSource();
                Tile clickedTile = (Tile) clickedBtn.getClientProperty("tileData");
                Area tileArea = board.getTileArea(clickedTile);

                //ABILITY LOGIC
                if (activeAbilityMap != null) {

                    //CODER LOGIC
                    if(activeAbilityMap.containsKey(Area.ANY) && activeAbilityMap.get(Area.ANY) == 0){
                        if(tileArea == Area.ENTRANCE){
                            System.out.println("Invalid area chosen");
                            return;
                        }

                        System.out.println("Coder Ability: Selected " + tileArea);
                        board.getCurrentPlayer().setCoderBonusArea(tileArea);

                        activeAbilityMap = null;
                        if (activeCharacterIndex != -1) {
                            board.getCurrentPlayer().getCharacters()[activeCharacterIndex][1] = true;
                        }
                        isAbilityUsed = true;
                        activeCharacterIndex = -1;
                        view.setNextTurnButtonEnabled(true);
                        return;
                    }

                    //STANDARD ABILITY LOGIC
                    if (!isMapEmpty(activeAbilityMap)) {
                        if (activeAbilityMap.containsKey(tileArea)) {
                            if (activeAbilityMap.get(tileArea) > 0) {
                                performPick(clickedTile);
                                activeAbilityMap.put(tileArea, activeAbilityMap.get(tileArea) - 1);
                            } else {
                                System.out.println("Blocked by specific rule");
                                return;
                            }
                        } else if (activeAbilityMap.containsKey(Area.ANY) && activeAbilityMap.get(Area.ANY) > 0) {
                            if (tileArea == Area.ENTRANCE) {
                                System.out.println("Cannot pick Landslide via wildcard");
                                return;
                            }
                            performPick(clickedTile);
                            activeAbilityMap.put(Area.ANY, activeAbilityMap.get(Area.ANY) - 1);
                        } else {
                            System.out.println("Invalid pick.");
                            return;
                        }

                        if (isMapEmpty(activeAbilityMap)) {
                            System.out.println("Ability Complete!");
                            activeAbilityMap = null;
                            if (activeCharacterIndex != -1) {
                                board.getCurrentPlayer().getCharacters()[activeCharacterIndex][1] = true;
                            }
                            isAbilityUsed = true;
                            activeCharacterIndex = -1;
                            view.setNextTurnButtonEnabled(true);
                        }
                    }
                    return;
                }

                // =======================================================
                // 2. NORMAL TURN LOGIC
                // =======================================================
                if (tilesDrawnCounter < 4) {
                    System.out.println("You must draw 4 tiles first");
                    return;
                }
                if (tilesChosen >= 2) {
                    System.out.println("Limit Reached: Finish turn or use ability");
                    return;
                }
                if(tileArea == Area.ENTRANCE){
                    System.out.println("Cannot choose landslide tiles");
                    return;
                }

                if (tilesChosen == 0) {
                    chosenAreaForCollection = tileArea;
                    System.out.println("First tile chosen from " + tileArea + ". Next must match.");
                    performPick(clickedTile);
                    tilesChosen++;
                    if(board.getAreas().get(chosenAreaForCollection).isEmpty()){
                        System.out.println("Second tile cant be chosen from area because area is empty\nFinishing tile selection...");
                        tilesChosen++;
                        view.setNextTurnButtonEnabled(true);
                    }
                }
                else if (tilesChosen == 1) {
                    if (tileArea == chosenAreaForCollection) {
                        System.out.println("Second tile matched! Collection complete.");
                        performPick(clickedTile);
                        tilesChosen++;
                        view.setNextTurnButtonEnabled(true);
                    } else {
                        System.out.println("Invalid! You must pick from " + chosenAreaForCollection);
                    }
                }
            }
        });
    }

    /**
     * Chooses a tile from the board
     */
    private static void performPick(Tile tile) {
        board.removeObject(board.getTileArea(tile), tile);
        board.getCurrentPlayer().addTile(tile);
        view.removeTileFromBoard(tile);
    }

    /**
     * Checker for map
     */
    private static boolean isMapEmpty(Map<Area, Integer> map) {
        for (int count : map.values()) {
            if (count > 0) return false;
        }
        return true;
    }

    /**
     * Saving process
     */
    // --- SAVE GAME --- //
    private static void saveGame() {
        try (java.io.ObjectOutputStream out = new java.io.ObjectOutputStream(new java.io.FileOutputStream("savegame.dat"))) {

            // save everything into an object array
            // 0=Board, 1=TilesDrawn, 2=TilesChosen, 3=TimeLeft, etc.
            Object[] saveData = {
                    board,
                    tilesDrawnCounter,
                    tilesChosen,
                    chosenAreaForCollection,
                    isAbilityUsed,
                    timeLeft
            };

            out.writeObject(saveData);
            System.out.println("Game Saved Successfully!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Loading process
     */
    // --- LOAD GAME --- //
    private static void loadGame() {
        try (java.io.ObjectInputStream in = new java.io.ObjectInputStream(new java.io.FileInputStream("savegame.dat"))) {

            // read the array back
            Object[] loadData = (Object[]) in.readObject();

            // cast back to original types

            board = (Board) loadData[0];
            tilesDrawnCounter = (int) loadData[1];
            tilesChosen = (int) loadData[2];
            chosenAreaForCollection = (Area) loadData[3];
            isAbilityUsed = (boolean) loadData[4];
            timeLeft = (int) loadData[5];

            // refresh the view
            view.clearAllTilesVisually();

            // fill the board gui
            for (Area area : Area.values()) {
                for (Tile tile : board.getAreas().get(area)) {
                    view.findWhereTileGoes(tile);
                }
            }

            // update labels

            view.updateBagCount(board.getMainBag().size());
            view.highlightPlayerTurn(board.getCurrentPlayerIndex());
            view.updateTimerDisplay(timeLeft);

            System.out.println("Game Loaded!");

        } catch (Exception e) {
            System.out.println("Load failed: " + e.getMessage());
        }
    }
}