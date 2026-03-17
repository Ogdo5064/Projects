package classes.model.Board;
import classes.model.Tiles.*;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class BoardTest {

    @Test
    void testGetTileArea_StatueGoesToStatue() {
        Board board = new Board(4);
        Tile statue = new StatueTile(-1);

        Area result = board.getTileArea(statue);

        assertEquals(Area.STATUE, result, "Statue tiles must belong to Area.STATUE");
    }

    @Test
    void testNextTurn_CyclesCorrectly() {
        Board board = new Board(4);

        assertEquals(0, board.getCurrentPlayerIndex());

        board.assignNextPlayerTurn();
        assertEquals(1, board.getCurrentPlayerIndex(), "Should move to Player 2 ");

        board.assignNextPlayerTurn();
        board.assignNextPlayerTurn();
        board.assignNextPlayerTurn();

        assertEquals(0, board.getCurrentPlayerIndex(), "Should cycle back to Player 1  after last player");
    }
    @Test
    void testGetTileArea_MosaicGoesToMosaic() {
        Board board = new Board(4);
        Tile mosaic = new MosaicTile(Color.RED,-1);

        Area result = board.getTileArea(mosaic);

        assertEquals(Area.MOSAIC, result, "Mosaic tiles should belong to Area.MOSAIC");
    }
    @Test
    void testBag_BecomesEmpty() {
        Board board = new Board(1);
        int Limit = 200;

        while (!board.getMainBag().isEmpty() && Limit > 0) {
            board.drawTile();
            Limit--;
        }

        assertTrue(board.getMainBag().isEmpty(), "Bag should report true for isEmpty()");

        assertNull(board.drawTile(), "Drawing from an empty bag should return null");
    }
}

