package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the mosaic tile in the game
 */
public class MosaicTile extends FindingTile implements Serializable {
    /**
     * Enum variable
     * The color of the mosaic tile
     * 3 available colors
     */
    private Color color;

    /**
     * Default constructor
     * @param color the color of the tile
     * @param points the points of the tile
     */
    public MosaicTile(Color color,int points) {
        super(points);
        setColor(color);
    }

    /**
     * Setter for color
     * @throws IllegalArgumentException is thrown when wrong color is given
     * @param color of the tile
     */
    public void setColor(Color color) {
        if (color == Color.RED || color == Color.YELLOW || color == Color.GREEN) {
            this.color = color;
        } else {
            throw new IllegalArgumentException("Invalid color for MosaicTile: " + color);
        }
    }

    /**
     * Getter for color
     * @return the color of the tile
     */
    public Color getColor() {
        return this.color;
    }
}

