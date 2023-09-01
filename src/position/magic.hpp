#pragma once
#include "bitboard.hpp"
#include "chess.hpp"
#define MAGICS_ARRAY_SIZE 200000

enum Direction : Offset {
    SOUTH = -8,
    NORTH = 8,
    WEST = -1,
    EAST = 1,
    SOUTH_WEST = SOUTH + WEST,
    SOUTH_EAST = SOUTH + EAST,
    NORTH_EAST = NORTH + EAST,
    NORTH_WEST = NORTH + WEST,
    SSW = SOUTH + SOUTH + WEST,
    SSE = SOUTH + SOUTH + EAST,
    EES = EAST + EAST + SOUTH,
    EEN = EAST + EAST + NORTH,
    NNE = NORTH + NORTH + EAST,
    NNW = NORTH + NORTH + WEST,
    WWN = WEST + WEST + NORTH,
    WWS = WEST + WEST + SOUTH
};

enum RayDirection : Offset {
    SOUTH_EAST_RAY,
    SOUTH_RAY,
    SOUTH_WEST_RAY,
    WEST_RAY,
    NORTH_WEST_RAY,
    NORTH_RAY,
    NORTH_EAST_RAY,
    EAST_RAY,
    POSITIVE = NORTH_WEST_RAY,
    RAY_COUNT = EAST_RAY + 1
};

inline Bitboard getMagicIndex(Bitboard board, Bitboard magic, uint8_t shift) {
    return (board * magic) >> shift;
}

class Magic {
  public:
    Bitboard *attacks;
    Bitboard magic;
    Bitboard mask;
    uint8_t shift;
    inline Bitboard getMagicIndex(Bitboard board) {
        return (board * magic) >> shift;
    }
    inline Bitboard getAttack(Bitboard occupation) {
        return attacks[getMagicIndex(occupation & mask)];
    }
};

extern std::array<Bitboard, MAGICS_ARRAY_SIZE> magics;
extern std::array<Magic, Square::SQUARE_COUNT> rookMagics;
extern std::array<Magic, Square::SQUARE_COUNT> bishopMagics;
extern std::array<std::array<Bitboard, Square::SQUARE_COUNT>, RayDirection::RAY_COUNT> rays;
extern std::array<Bitboard, Square::SQUARE_COUNT> rankAttacks;
extern std::array<Bitboard, Square::SQUARE_COUNT> fileAttacks;
extern std::array<std::array<Bitboard, Square::SQUARE_COUNT>, 2> pawnAttacks;
extern std::array<Bitboard, Square::SQUARE_COUNT> knightAttacks;
extern std::array<Bitboard, Square::SQUARE_COUNT> kingAttacks;
extern std::array<Bitboard, Square::SQUARE_COUNT> bishopMasks;
extern std::array<Bitboard, Square::SQUARE_COUNT> rookMasks;
extern std::array<Bitboard, Square::SQUARE_COUNT> queenMasks;
extern std::array<std::array<Bitboard, Square::SQUARE_COUNT>, 2> pawnPushes;
extern std::array<std::array<Bitboard, Square::SQUARE_COUNT>, 2> pawnDoublePushes;
extern std::array<Bitboard, Square::SQUARE_COUNT> maskedSquare;
extern std::array<Bitboard, Square::SQUARE_COUNT> unmaskedSquare;
extern std::array<std::array<Bitboard, Square::SQUARE_COUNT>, Square::SQUARE_COUNT> inBetween;

void initGlobals();

void initPrimitives();
void initMagics();
void initRayAttacks();

Magic initMagicSquare(SquareIndex index, bool bishop, uint64_t *magicIndex);

Bitboard getRayAttacks(Bitboard occupied, RayDirection direction, SquareIndex square);

// Line attacks
Bitboard getDiagonalMask(SquareIndex index);
Bitboard getDiagonal2Mask(SquareIndex index);
Bitboard getRankMask(SquareIndex index);
Bitboard getFileMask(SquareIndex index);

// Piece attacks
Bitboard getQueenMask(SquareIndex index);
Bitboard getRookMask(SquareIndex index);
Bitboard getBishopMask(SquareIndex index);

Bitboard getKnightAttacks(Bitboard board);
Bitboard getKingAttacks(Bitboard board);
Bitboard getBishopAttacks(SquareIndex index, Bitboard occupancy);
Bitboard getRookAttacks(SquareIndex index, Bitboard occupancy);

void printRays(SquareIndex index);
void printKnightAttacks();

constexpr std::array<Bitboard, Square::SQUARE_COUNT> bishopMagicNumbers = {
    297457482031202818ULL,   1423718041586254880ULL,  4612834200762974208ULL,
    1527041337516359808ULL,  299344188145698ULL,      9243675691856363650ULL,
    666815356555232256ULL,   10754667412785726720ULL, 396334498041630787ULL,
    576462959952400898ULL,   54087185661561984ULL,    2350888918288957440ULL,
    36029966323810304ULL,    4611686611680247872ULL,  2314851326252550144ULL,
    27022184162001476ULL,    1212176402970312972ULL,  2537690285244928ULL,
    2340396466438160ULL,     4644508947989768ULL,     3604006710175467586ULL,
    17169982186095136ULL,    281552306045440ULL,      2322789185097764ULL,
    5103934052516352ULL,     18304704023897104ULL,    72215923884556416ULL,
    23089744217379072ULL,    20411335544152080ULL,    13853215394600456192ULL,
    4612816385104759813ULL,  517984601852087360ULL,   9516123644548614144ULL,
    10381361538448491008ULL, 1126209211663888ULL,     4611811364900962432ULL,
    594485050712526912ULL,   4611968635903213632ULL,  9944572508438597760ULL,
    11533456970653663568ULL, 144401072373383296ULL,   1200958822440992ULL,
    435161414118672384ULL,   275150537218ULL,         1175448337558569232ULL,
    9008324605445634ULL,     4613940859145061440ULL,  9248142935969497604ULL,
    9241527825826061328ULL,  5262504629027480704ULL,  283602322432ULL,
    52778773004294ULL,       1161937568708198404ULL,  648629467916404736ULL,
    18067488617074688ULL,    9245892818134663168ULL,  9872453925991490048ULL,
    108093061158404608ULL,   577023706619057668ULL,   9223407272800682497ULL,
    9017096201701504ULL,     145245658143004160ULL,   2454753201996955736ULL,
    306253579411275793ULL};

constexpr std::array<Bitboard, Square::SQUARE_COUNT> rookMagicNumbers = {
    13690107169217112945ULL, 16909595728155107665ULL, 2123063628860269946ULL,
    4035226808834661160ULL,  10673531117694526752ULL, 8029918397703717678ULL,
    13083562878446252480ULL, 15348544270174257352ULL, 13490017405117343787ULL,
    8976843990658957604ULL,  10301576892330630232ULL, 2801666492023295514ULL,
    2195460232856257226ULL,  9861605857932418839ULL,  2370960713037578680ULL,
    8995993997382192215ULL,  17645229281959348862ULL, 4343735920766361682ULL,
    8527900304227474261ULL,  15248505431190655918ULL, 8468485666890730719ULL,
    3593327757119613731ULL,  4944687269947111446ULL,  10891129446546179135ULL,
    14506584874387329460ULL, 12475756400726558594ULL, 8868854299685176115ULL,
    7062026289669462742ULL,  3587804798274248587ULL,  12536978651472206209ULL,
    13390965344739446724ULL, 7912357913542973796ULL,  17823648541676567844ULL,
    16722818710209391447ULL, 7973884559592848249ULL,  1947170467483581565ULL,
    929409657981818811ULL,   5523487018808776837ULL,  412796121279209087ULL,
    7980520628053083201ULL,  13865347327246038093ULL, 10466271025676773978ULL,
    12684523333682236008ULL, 8299416087271348697ULL,  15886841937149808343ULL,
    12588971971775504954ULL, 3851323264607735111ULL,  5393983275302947581ULL,
    5737754750552644888ULL,  3065736249640606639ULL,  12282193848289045012ULL,
    2378441412753549833ULL,  12828441701529618822ULL, 6658972368620906761ULL,
    5105258127260727247ULL,  15233245419673223509ULL, 10341412856083681315ULL,
    14227638693931018045ULL, 1659301358219503768ULL,  5226745756237626584ULL,
    3362399540765309368ULL,  6695002540660917772ULL,  275795561066525719ULL,
    13084604094040956754ULL};
