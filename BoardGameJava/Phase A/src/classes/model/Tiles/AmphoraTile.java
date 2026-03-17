package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the amphora tile of the game
 */
public class AmphoraTile extends FindingTile implements Serializable {

    /**
     * Enum variable
     * The color of the tile
     * 6 colors
     */
    private Color color;

    /**
     * Default constructor
     * @param color of the tile
     * @param points of the tile
     */
    public AmphoraTile(Color color,int points){
        super(points);
        setColor(color);
    }

    /**
     * Setter for the color
     * @param color of the tile
     */
    public void setColor(Color color){this.color = color;}

    /**
     * Getter for the color
     * @return the color of the tile
     */
    public Color getColor(){return this.color;}
}
