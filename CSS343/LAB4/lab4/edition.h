/*---------------------------------------------------------------------------
Edition
Detail on an edition for a publication. Books may have a soft and hard cover.
Books may also have a series of edition (1, 2, 3, 4, 5)
Videos may have DVD, BD, MP4


Features:

Assumptions:
    --Edition types are known
---------------------------------------------------------------------------*/
enum Editions {
    HARDCOVER = 'H',
    SOFTCOVER = 'S',
    DVD = 'D',
    BLURAY = 'B'
};

class Edition {
    Edition(Editions, int = 0);
    ~Edition();

    void setEdition(Editions);
    Editions getEdition();

private:
    Editions PubEdition;
    int numberEdition;
};