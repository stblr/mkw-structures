/*
ItemSlotData is the class that handles data from ItemSlot.bin / ItemSlotTable.slt
A pointer to an instance of this class is stored at 0x809c3670 PAL
See also http://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/ItemSlot.bin
*/

class PlayerHolderSub { // This'll get moved once I figure out what it is properly or write up PlayerHolder info
public: 
  virtual ~PlayerHolderSub(); // 8021a144 PAL
  PlayerHolderSub(); // 8021a0f0 PAL
  
  // vtable 802a2b48 PAL
  void * unknown_0x4;
  void * unknown_0x8;
  void * unknown_0xC;
}; // Total size 0x10

typedef struct {
  uint32_t columns;
  short * data;
} ItemSlotTableHolder; // Total size 0x8

class ItemSlotData : public PlayerHolderSub {
public:
  virtual ~ItemSlotData(); // 807ba650 PAL
  int decideItem(int itemboxSetting, int position, int r6, int r7, void * r8); // 807bb42c PAL
  uint8_t * processTableAndIter(uint8_t * itemTable, ItemSlotTableHolder * tableHolder, bool updateItemsInWheek, bool isSpecialTable); // 807ba9d8 PAL, takes a pointer to a raw table in an item slot file, processes the values and writes them to the data field of the table holder, then returns the pointer to the start of the next table
  void scaleTableForPlayerCount(ItemSlotTableHolder * tableHolder)// 807bad20 PAL
  void resetLightningTimer(); // 807bb9bc PAL
  void resetBlueShellTimer(); // 807bb9c8 PAL, goes unused
  void resetBlooperTimer(); // 807bb9d4 PAL
  void resetPowTimer(); // 807bb9e0 PAL
  void updateTimers(); // 807bb9ec PAL, also responsible for setting them to their initial values on the first frame
  bool checkSpawnTimer(int objectId, int r5); // 807bb380 (from Star)
  // Always constructed inline
  
  // vtable 808d27b4 PAL
  ItemSlotTableHolder playerChances;
  ItemSlotTableHolder cpuChances;
  ItemSlotTableHolder specialChances;
  int * itemsInWheel; // first int is number of items, followed by the item ids (visual only, doesn't stop you pulling other items)
  int * specialBoxItemsInWheel; // a series of lists in same structure as itemsInWheel, one for each column of the special table
  // unknown 0x30-33
  unsigned int[4] itemSpawnTimers; // timers in frames for when an item can next be pulled. 0 = lightning, 1 = blue shell, 2 = blooper, 3 = pow
  unsigned int playerCount; // copied from the global variable by constructor, used to check when the player count changes online
}; // Total size 0x48
