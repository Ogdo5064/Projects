package classes.View;

import classes.model.Board.Board;
import classes.model.Player.Player;
import classes.model.Tiles.*;

import javax.swing.*;
import java.awt.*;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Viewer {

    private JFrame gameWindow;
    private JFrame controlWindow;

    private Map<Integer, JPanel> boardCells = new HashMap<>();

    private JButton[] playerButtons;

    private JButton[][] characterButtons;

    private JButton drawTileButton;

    private JLabel centerBagLabel;

    private JButton nextTurnButton;

    private ActionListener tileClickListener;

    private JButton[] backpackButtons;

    private JLabel timerLabel;

    private JMenuItem saveItem;
    private JMenuItem loadItem;


    /**
     * Initializes all the UI
     */
    public void initializeUI(ArrayList <Player> players) {
        gamingBoardGUI();
        playerInfoGUI(players);
        timerLabel = new JLabel("Time: 30", SwingConstants.CENTER);
        timerLabel.setFont(new Font("Arial", Font.BOLD, 24));
        timerLabel.setForeground(Color.RED);
        timerLabel.setOpaque(false);
        timerLabel.setBackground(Color.WHITE);
        //timerLabel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));

        gameWindow.add(timerLabel, BorderLayout.NORTH);

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int width = (int) screenSize.getWidth();
        int height = (int) screenSize.getHeight();

        gameWindow.setSize(width - 350, height);
        gameWindow.setLocation(0, 0);


        controlWindow.setSize(350, height);
        controlWindow.setLocation(width - 350, 0);

        controlWindow.setAlwaysOnTop(true);

    }

    /**
     * Shows the needed players for the game (1 or 4)
     */
    public void updateVisiblePlayers(int numPlayers) {
        for (int i = 0; i < 4; i++) {
            boolean shouldShow = (i < numPlayers);

            if (playerButtons[i] != null) playerButtons[i].setVisible(shouldShow);


            if (backpackButtons[i] != null) backpackButtons[i].setVisible(shouldShow);

            for (int j = 0; j < 5; j++) {
                if (characterButtons[i][j] != null) {
                    if (!shouldShow) {
                        characterButtons[i][j].setVisible(false);
                    }
                }
            }
        }
    }

    /**
     * Wipes all tile buttons from the board panels
     * Required before loading a saved game to prevent duplicates
     */
    public void clearAllTilesVisually() {
        // boardCells contains all my grids 1-3-5-7-9
        for (JPanel areaPanel : boardCells.values()) {
            if (areaPanel != null) {
                areaPanel.removeAll();  // delete all buttons
                areaPanel.revalidate(); // reset layout
                areaPanel.repaint();    // redraw screen
            }
        }
    }

    public void addSaveListener(ActionListener l) {
        if (this.saveItem != null) {
            this.saveItem.addActionListener(l);
        }
    }

    public void addLoadListener(ActionListener l) {
        if (this.loadItem != null) {
            this.loadItem.addActionListener(l);
        }
    }

    /**
     * Timer updater for each turn
     */
    public void updateTimerDisplay(int seconds) {
        timerLabel.setText("Time: " + seconds);
        if (seconds <= 5) {
            timerLabel.setForeground(Color.RED);
        } else {
            timerLabel.setForeground(Color.BLACK);
        }
    }

    public void setTileClickListener(ActionListener listener) {
        this.tileClickListener = listener;
    }


    /**
     * GUI initialization for main game board
     * JFrame for picture rescaling
     */
    public void gamingBoardGUI() {
        gameWindow = new JFrame("Amphipolis - Board");
        gameWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        gameWindow.setMinimumSize(new Dimension(1024, 768));
        gameWindow.setExtendedState(JFrame.MAXIMIZED_BOTH);

        ImageIcon originalIcon = new ImageIcon("src/assets/images/backgroundMaybe.png");
        Image bgImage = originalIcon.getImage();

        JPanel backgroundPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                if (bgImage != null) {
                    g.drawImage(bgImage, 0, 0, getWidth(), getHeight(), this);
                }
            }
        };
        backgroundPanel.setLayout(new BorderLayout());

        JPanel gridPanel = new JPanel();
        gridPanel.setLayout(new GridLayout(3, 3, 5, 5));
        gridPanel.setOpaque(false); // Invisible

        int[] tileGridPositions = {1, 3, 5, 7, 9};

        ImageIcon bagIcon = new ImageIcon("src/assets/images/mainBag.png");
        Image bagImg = bagIcon.getImage().getScaledInstance(100, 100, Image.SCALE_SMOOTH);
        ImageIcon scaledBagIcon = new ImageIcon(bagImg);

        for (int i = 1; i <= 9; i++) {
            boolean isTileGrid = false;
            for (int pos : tileGridPositions) { if (i == pos) isTileGrid = true; }

            if (isTileGrid) {
                JPanel cellPanel = new JPanel();
                cellPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 2, 2));

                cellPanel.setOpaque(false);

                boardCells.put(i, cellPanel);
                gridPanel.add(cellPanel);
            }
            else if (i == 2) {
                centerBagLabel = new JLabel(scaledBagIcon);
                centerBagLabel.setText("0");
                centerBagLabel.setHorizontalTextPosition(JLabel.CENTER);
                centerBagLabel.setVerticalTextPosition(JLabel.CENTER);
                centerBagLabel.setForeground(Color.WHITE);
                centerBagLabel.setFont(new Font("Arial", Font.BOLD, 30));
                gridPanel.add(centerBagLabel);
            }
            else {
                gridPanel.add(new JLabel(""));
            }
        }

        backgroundPanel.add(gridPanel, BorderLayout.CENTER);

        JMenuBar menuBar = new JMenuBar();
        JMenu gameMenu = new JMenu("Game Options");
        saveItem = new JMenuItem("Save Game");
        loadItem = new JMenuItem("Load Game");
        gameMenu.add(saveItem);
        gameMenu.add(loadItem);
        menuBar.add(gameMenu);
        gameWindow.setJMenuBar(menuBar);

        gameWindow.setContentPane(backgroundPanel);
        gameWindow.setVisible(true);
    }


    /**
     * Initialization for the player interaction panel
     */
    public void playerInfoGUI(ArrayList<Player> players) {

        controlWindow = new JFrame("Controls");
        controlWindow.setSize(1100, 900);
        controlWindow.setResizable(true);
        controlWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        controlWindow.setLocation(400, 100);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.add(Box.createVerticalStrut(20));

        playerButtons = new JButton[4];
        characterButtons = new JButton[4][5];
        backpackButtons = new JButton[4];

        for (int i = 0; i < players.size(); i++) {
            JPanel rowPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 15, 5));
            rowPanel.setMaximumSize(new Dimension(1100, 170));

            playerButtons[i] = new JButton(players.get(i).getName());
            playerButtons[i].setPreferredSize(new Dimension(220, 100));
            playerButtons[i].setFont(new Font("Arial", Font.BOLD, 22));
            playerButtons[i].setFocusable(false);
            backpackButtons[i] = new JButton("Bag");
            backpackButtons[i].setPreferredSize(new Dimension(70, 40));
            backpackButtons[i].setFocusable(false);
            rowPanel.add(backpackButtons[i]);
            rowPanel.add(playerButtons[i]);

            for (int j = 0; j < 5; j++) {
                JButton charBtn = new JButton();
                charBtn.setPreferredSize(new Dimension(110, 150));

                charBtn.setFocusable(false);
                charBtn.setVisible(false);
                charBtn.setBorderPainted(false);
                charBtn.setContentAreaFilled(false);
                charBtn.setMargin(new Insets(0,0,0,0));

                charBtn.setBorder(BorderFactory.createLineBorder(Color.YELLOW, 3)); // Yellow highlight

                charBtn.addMouseListener(new java.awt.event.MouseAdapter() {
                    public void mouseEntered(java.awt.event.MouseEvent evt) {
                        charBtn.setBorderPainted(true);
                        charBtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
                    }

                    public void mouseExited(java.awt.event.MouseEvent evt) {
                        charBtn.setBorderPainted(false);
                        charBtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
                    }
                });

                characterButtons[i][j] = charBtn;
                rowPanel.add(charBtn);
            }

            mainPanel.add(rowPanel);
            mainPanel.add(Box.createVerticalStrut(10));
        }

        mainPanel.add(Box.createVerticalStrut(30));
        drawTileButton = new JButton("Draw Tile");
        drawTileButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        drawTileButton.setPreferredSize(new Dimension(250, 80));
        drawTileButton.setFont(new Font("Arial", Font.BOLD, 24));

        JPanel btnPanel = new JPanel();
        btnPanel.add(drawTileButton);
        mainPanel.add(btnPanel);

        nextTurnButton = new JButton("Finish Turn");
        nextTurnButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        nextTurnButton.setPreferredSize(new Dimension(200, 60));
        nextTurnButton.setFont(new Font("Arial", Font.BOLD, 18));
        nextTurnButton.setEnabled(false);

        mainPanel.add(Box.createVerticalStrut(20));
        JPanel btnPanel2 = new JPanel();
        btnPanel2.add(nextTurnButton);
        mainPanel.add(btnPanel2);

        controlWindow.add(mainPanel);
        controlWindow.setVisible(true);
    }

    /**
     * Enables-Disables the draw button (locks user after 4 draws)
     */
    public void setDrawButtonEnabled(boolean isEnabled) {
        this.drawTileButton.setEnabled(isEnabled);
    }

    /**
     * Enables-Disables next turn button (locks user until a rule is fulfilled)
     */
    public void setNextTurnButtonEnabled(boolean isEnabled) {
        this.nextTurnButton.setEnabled(isEnabled);
    }


    public void addNextTurnButtonListener(ActionListener l) {
        this.nextTurnButton.addActionListener(l);
    }

    public void addBackpackButtonListeners(int playerIndex, ActionListener l) {
        if (backpackButtons[playerIndex] != null) {
            backpackButtons[playerIndex].addActionListener(l);
        }
    }

    /**
     * Shows-Hides the character selection row
     * If shown -> hide
     * If hidden -> show
     */
    public void toggleCharacterRow(int playerIndex) {
        boolean isVisible = characterButtons[playerIndex][0].isVisible();
        boolean newState = !isVisible;

        for (int j = 0; j < 5; j++) {
            characterButtons[playerIndex][j].setVisible(newState);
        }
    }

    /**
     * Sets an icon for a specific character button
     */
    public void setCharacterIcon(int playerIndex, int charIndex, String imagePath) {
        JButton btn = characterButtons[playerIndex][charIndex];

        ImageIcon icon = new ImageIcon(imagePath);
        Image img = icon.getImage().getScaledInstance(110, 150, Image.SCALE_SMOOTH);

        btn.setIcon(new ImageIcon(img));
    }


    public void addPlayerButtonListener(int playerIndex, java.awt.event.ActionListener l) {
        playerButtons[playerIndex].addActionListener(l);
    }

    public void addCharacterButtonListener(int pIndex, int cIndex, java.awt.event.ActionListener l) {
        characterButtons[pIndex][cIndex].addActionListener(l);
    }

    public void addDrawButtonListener(java.awt.event.ActionListener l) {
        drawTileButton.addActionListener(l);
    }

    /**
     * Adds a tile to the corresponding grid area
     */
    public void addTileLeftUp(Tile tile) { updateBoardCell(1, tile); }
    public void addTileRightUp(Tile tile) { updateBoardCell(3, tile); }
    public void addTileLeftDown(Tile tile) { updateBoardCell(7, tile); }
    public void addTileRightDown(Tile tile) { updateBoardCell(9, tile); }
    public void addTileCenter(Tile tile) { updateBoardCell(5, tile); }

    /**
     * Helper to update the grid cell with a tile image as a button
     */
    private void updateBoardCell(int posId, Tile tile) {
        JPanel cellPanel = boardCells.get(posId);

        if (cellPanel != null && tile != null) {
            String path = getTileImagePath(tile);
            ImageIcon icon = new ImageIcon(path);
            Image img = icon.getImage().getScaledInstance(40, 40, Image.SCALE_SMOOTH);

            JButton tileButton = new JButton(new ImageIcon(img));

            tileButton.setPreferredSize(new Dimension(40, 40));
            tileButton.setBorderPainted(false);
            tileButton.setContentAreaFilled(false);
            tileButton.setFocusable(false);

            // attaches data onto a button
            tileButton.putClientProperty("tileData", tile);

            if (this.tileClickListener != null) {
                tileButton.addActionListener(this.tileClickListener);
            }

            cellPanel.add(tileButton);
            cellPanel.revalidate();
            cellPanel.repaint();
        }
    }

    /**
     * Helper to remove a specific tile button from the screen
     */
    public void removeTileFromBoard(Tile tileToRemove) {
        for (JPanel panel : boardCells.values()) {
            if (panel == null) continue;

            //JPanel contains many different objects (buttons,labels,panels)
            //getComponents returns an array with all those objects in that JPanel
            //If the component is of JButton instance -> If tile == tileToRemove then remove it
            Component[] components = panel.getComponents();
            for (Component c : components) {
                if (c instanceof JButton) {
                    JButton btn = (JButton) c;
                    Tile t = (Tile) btn.getClientProperty("tileData");
                    // retrieves data from a button
                    // attached previously with getClientProperty

                    if (t == tileToRemove) {
                        panel.remove(btn);
                        panel.revalidate();
                        panel.repaint();
                        return;
                    }
                }
            }
        }
    }


    /**
     * Finds the exact name of the image path according to it's instance
     */
    private String getTileImagePath(Tile tile) {
        String basePath = "src/assets/images/";

        if (tile instanceof AmphoraTile) {
            AmphoraTile t = (AmphoraTile) tile;
            return basePath + "amphora_" + t.getColor().toString().toLowerCase() + ".png";
        }

        else if (tile instanceof MosaicTile) {
            MosaicTile t = (MosaicTile) tile;
            return basePath + "mosaic_" + t.getColor().toString().toLowerCase() + ".png";
        }

        else if (tile instanceof SkeletonTile) {
            SkeletonTile t = (SkeletonTile) tile;
            String suffix = "";

            switch (t.getType()) {
                case BIG_UPPER:   suffix = "big_top"; break;
                case BIG_LOWER:   suffix = "big_bottom"; break;
                case SMALL_UPPER: suffix = "small_top"; break;
                case SMALL_LOWER: suffix = "small_bottom"; break;
            }
            return basePath + "skeleton_" + suffix + ".png";
        }

        else if (tile instanceof CaryatidTile) {
            return basePath + "caryatid.png";
        }
        else if (tile instanceof SphinxTile) {
            return basePath + "sphinx.png";
        }
        else if (tile instanceof LandslideTile) {
            return basePath + "landslide.png";
        }

        return basePath + "tile_back.png";
    }

    public void updateBagCount(int remainingTiles) {
        if (this.centerBagLabel != null) {
            this.centerBagLabel.setText(String.valueOf(remainingTiles));
            this.centerBagLabel.repaint();
        }
    }

    /**
     * Self-explanatory
     */
    public void findWhereTileGoes(Tile tile){
        if (tile instanceof AmphoraTile) {
            addTileLeftDown(tile);
        }
        else if(tile instanceof SkeletonTile){
            addTileRightDown(tile);
        }
        else if(tile instanceof MosaicTile){
            addTileLeftUp(tile);
        }
        else if(tile instanceof StatueTile){
            addTileRightUp(tile);
        }
        else if(tile instanceof LandslideTile){
            addTileCenter(tile);
        }
    }

    /**
     * Highlights the current player's name
     */
    public void highlightPlayerTurn(int playerIndex) {
        Color activeColor = Color.CYAN;
        Color defaultColor = UIManager.getColor("Button.background");

        for (int i = 0; i < playerButtons.length; i++) {
            if(playerButtons[i] == null){
                continue;
            }
            if (i == playerIndex) {
                //System.out.println("Coloring player with player index:"+playerIndex);
                playerButtons[i].setBackground(activeColor);

                playerButtons[i].setForeground(Color.BLACK);
                playerButtons[i].setFont(new Font("Arial", Font.BOLD, 22));

                playerButtons[i].setBorder(BorderFactory.createLineBorder(Color.BLACK, 3));
            } else {
                playerButtons[i].setBackground(defaultColor);
                playerButtons[i].setForeground(Color.BLACK);
                playerButtons[i].setFont(new Font("Arial", Font.PLAIN, 22));
                playerButtons[i].setBorder(UIManager.getBorder("Button.border"));
            }
        }
    }

    /**
     * Backpack viewer logic
     * If empty shows a text
     */
    public void showBackpackDialog(String playerName, java.util.List<Tile> tiles) {
        JPanel panel = new JPanel();
        panel.setLayout(new FlowLayout(FlowLayout.LEFT, 5, 5));
        panel.setPreferredSize(new Dimension(400, 300));

        if (tiles == null || tiles.isEmpty()) {
            panel.add(new JLabel("Backpack is empty!"));
        } else {
            for (Tile t : tiles) {
                String path = getTileImagePath(t);
                ImageIcon icon = new ImageIcon(path);
                Image img = icon.getImage().getScaledInstance(50, 50, Image.SCALE_SMOOTH);
                JLabel tileLabel = new JLabel(new ImageIcon(img));
                panel.add(tileLabel);
            }
        }

        JOptionPane.showMessageDialog(null, panel, playerName + "'s Backpack", JOptionPane.PLAIN_MESSAGE);
    }
}