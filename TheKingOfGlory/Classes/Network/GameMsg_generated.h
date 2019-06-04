// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_GAMEMSG_GAMEMSG_H_
#define FLATBUFFERS_GENERATED_GAMEMSG_GAMEMSG_H_

#include "flatbuffers/flatbuffers.h"

namespace GameMsg {

struct Point;

struct Player;

struct GameInit;

struct PlayerMove;

struct PlayerAttack;

struct PlayerSkill;

struct PlayerExit;

struct GameOver;

struct Msg;

enum MsgType {
  MsgType_MsgType_None = 0,
  MsgType_MsgType_GameInit = 1,
  MsgType_MsgType_PlayerMove = 2,
  MsgType_MsgType_PlayerAttack = 3,
  MsgType_MsgType_PlayerSkill = 4,
  MsgType_MsgType_GameOver = 5,
  MsgType_MsgType_PlayerExit = 6,
  MsgType_MIN = MsgType_MsgType_None,
  MsgType_MAX = MsgType_MsgType_PlayerExit
};

inline const MsgType (&EnumValuesMsgType())[7] {
  static const MsgType values[] = {
    MsgType_MsgType_None,
    MsgType_MsgType_GameInit,
    MsgType_MsgType_PlayerMove,
    MsgType_MsgType_PlayerAttack,
    MsgType_MsgType_PlayerSkill,
    MsgType_MsgType_GameOver,
    MsgType_MsgType_PlayerExit
  };
  return values;
}

inline const char * const *EnumNamesMsgType() {
  static const char * const names[] = {
    "MsgType_None",
    "MsgType_GameInit",
    "MsgType_PlayerMove",
    "MsgType_PlayerAttack",
    "MsgType_PlayerSkill",
    "MsgType_GameOver",
    "MsgType_PlayerExit",
    nullptr
  };
  return names;
}

inline const char *EnumNameMsgType(MsgType e) {
  if (e < MsgType_MsgType_None || e > MsgType_MsgType_PlayerExit) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesMsgType()[index];
}

enum SkillType {
  SkillType_One = 0,
  SkillType_Two = 1,
  SkillType_Three = 2,
  SkillType_MIN = SkillType_One,
  SkillType_MAX = SkillType_Three
};

inline const SkillType (&EnumValuesSkillType())[3] {
  static const SkillType values[] = {
    SkillType_One,
    SkillType_Two,
    SkillType_Three
  };
  return values;
}

inline const char * const *EnumNamesSkillType() {
  static const char * const names[] = {
    "One",
    "Two",
    "Three",
    nullptr
  };
  return names;
}

inline const char *EnumNameSkillType(SkillType e) {
  if (e < SkillType_One || e > SkillType_Three) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesSkillType()[index];
}

enum Color {
  Color_Red = 0,
  Color_Blue = 1,
  Color_MIN = Color_Red,
  Color_MAX = Color_Blue
};

inline const Color (&EnumValuesColor())[2] {
  static const Color values[] = {
    Color_Red,
    Color_Blue
  };
  return values;
}

inline const char * const *EnumNamesColor() {
  static const char * const names[] = {
    "Red",
    "Blue",
    nullptr
  };
  return names;
}

inline const char *EnumNameColor(Color e) {
  if (e < Color_Red || e > Color_Blue) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesColor()[index];
}

enum RoleType {
  RoleType_Warrior = 0,
  RoleType_Mage = 1,
  RoleType_Archer = 2,
  RoleType_MIN = RoleType_Warrior,
  RoleType_MAX = RoleType_Archer
};

inline const RoleType (&EnumValuesRoleType())[3] {
  static const RoleType values[] = {
    RoleType_Warrior,
    RoleType_Mage,
    RoleType_Archer
  };
  return values;
}

inline const char * const *EnumNamesRoleType() {
  static const char * const names[] = {
    "Warrior",
    "Mage",
    "Archer",
    nullptr
  };
  return names;
}

inline const char *EnumNameRoleType(RoleType e) {
  if (e < RoleType_Warrior || e > RoleType_Archer) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesRoleType()[index];
}

enum Date {
  Date_NONE = 0,
  Date_gameInit = 1,
  Date_playerMove = 2,
  Date_playerAttack = 3,
  Date_playerSkill = 4,
  Date_gameOver = 5,
  Date_playerExit = 6,
  Date_MIN = Date_NONE,
  Date_MAX = Date_playerExit
};

inline const Date (&EnumValuesDate())[7] {
  static const Date values[] = {
    Date_NONE,
    Date_gameInit,
    Date_playerMove,
    Date_playerAttack,
    Date_playerSkill,
    Date_gameOver,
    Date_playerExit
  };
  return values;
}

inline const char * const *EnumNamesDate() {
  static const char * const names[] = {
    "NONE",
    "gameInit",
    "playerMove",
    "playerAttack",
    "playerSkill",
    "gameOver",
    "playerExit",
    nullptr
  };
  return names;
}

inline const char *EnumNameDate(Date e) {
  if (e < Date_NONE || e > Date_playerExit) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesDate()[index];
}

template<typename T> struct DateTraits {
  static const Date enum_value = Date_NONE;
};

template<> struct DateTraits<GameInit> {
  static const Date enum_value = Date_gameInit;
};

template<> struct DateTraits<PlayerMove> {
  static const Date enum_value = Date_playerMove;
};

template<> struct DateTraits<PlayerAttack> {
  static const Date enum_value = Date_playerAttack;
};

template<> struct DateTraits<PlayerSkill> {
  static const Date enum_value = Date_playerSkill;
};

template<> struct DateTraits<GameOver> {
  static const Date enum_value = Date_gameOver;
};

template<> struct DateTraits<PlayerExit> {
  static const Date enum_value = Date_playerExit;
};

bool VerifyDate(flatbuffers::Verifier &verifier, const void *obj, Date type);
bool VerifyDateVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Point FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;

 public:
  Point() {
    memset(static_cast<void *>(this), 0, sizeof(Point));
  }
  Point(float _x, float _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(Point, 8);

struct Player FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_COLOR = 6,
    VT_ROLE = 8
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  Color color() const {
    return static_cast<Color>(GetField<int8_t>(VT_COLOR, 0));
  }
  RoleType role() const {
    return static_cast<RoleType>(GetField<int8_t>(VT_ROLE, 0));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int8_t>(verifier, VT_COLOR) &&
           VerifyField<int8_t>(verifier, VT_ROLE) &&
           verifier.EndTable();
  }
};

struct PlayerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Player::VT_NAME, name);
  }
  void add_color(Color color) {
    fbb_.AddElement<int8_t>(Player::VT_COLOR, static_cast<int8_t>(color), 0);
  }
  void add_role(RoleType role) {
    fbb_.AddElement<int8_t>(Player::VT_ROLE, static_cast<int8_t>(role), 0);
  }
  explicit PlayerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PlayerBuilder &operator=(const PlayerBuilder &);
  flatbuffers::Offset<Player> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Player>(end);
    return o;
  }
};

inline flatbuffers::Offset<Player> CreatePlayer(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    Color color = Color_Red,
    RoleType role = RoleType_Warrior) {
  PlayerBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_role(role);
  builder_.add_color(color);
  return builder_.Finish();
}

inline flatbuffers::Offset<Player> CreatePlayerDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    Color color = Color_Red,
    RoleType role = RoleType_Warrior) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return GameMsg::CreatePlayer(
      _fbb,
      name__,
      color,
      role);
}

struct GameInit FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RANDSEED = 4,
    VT_PLAYERS = 6
  };
  float randSeed() const {
    return GetField<float>(VT_RANDSEED, 0.0f);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Player>> *players() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Player>> *>(VT_PLAYERS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_RANDSEED) &&
           VerifyOffset(verifier, VT_PLAYERS) &&
           verifier.VerifyVector(players()) &&
           verifier.VerifyVectorOfTables(players()) &&
           verifier.EndTable();
  }
};

struct GameInitBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_randSeed(float randSeed) {
    fbb_.AddElement<float>(GameInit::VT_RANDSEED, randSeed, 0.0f);
  }
  void add_players(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Player>>> players) {
    fbb_.AddOffset(GameInit::VT_PLAYERS, players);
  }
  explicit GameInitBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  GameInitBuilder &operator=(const GameInitBuilder &);
  flatbuffers::Offset<GameInit> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GameInit>(end);
    return o;
  }
};

inline flatbuffers::Offset<GameInit> CreateGameInit(
    flatbuffers::FlatBufferBuilder &_fbb,
    float randSeed = 0.0f,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Player>>> players = 0) {
  GameInitBuilder builder_(_fbb);
  builder_.add_players(players);
  builder_.add_randSeed(randSeed);
  return builder_.Finish();
}

inline flatbuffers::Offset<GameInit> CreateGameInitDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    float randSeed = 0.0f,
    const std::vector<flatbuffers::Offset<Player>> *players = nullptr) {
  auto players__ = players ? _fbb.CreateVector<flatbuffers::Offset<Player>>(*players) : 0;
  return GameMsg::CreateGameInit(
      _fbb,
      randSeed,
      players__);
}

struct PlayerMove FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_POS = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const Point *pos() const {
    return GetStruct<const Point *>(VT_POS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<Point>(verifier, VT_POS) &&
           verifier.EndTable();
  }
};

struct PlayerMoveBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(PlayerMove::VT_NAME, name);
  }
  void add_pos(const Point *pos) {
    fbb_.AddStruct(PlayerMove::VT_POS, pos);
  }
  explicit PlayerMoveBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PlayerMoveBuilder &operator=(const PlayerMoveBuilder &);
  flatbuffers::Offset<PlayerMove> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerMove>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerMove> CreatePlayerMove(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    const Point *pos = 0) {
  PlayerMoveBuilder builder_(_fbb);
  builder_.add_pos(pos);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlayerMove> CreatePlayerMoveDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const Point *pos = 0) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return GameMsg::CreatePlayerMove(
      _fbb,
      name__,
      pos);
}

struct PlayerAttack FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct PlayerAttackBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(PlayerAttack::VT_NAME, name);
  }
  explicit PlayerAttackBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PlayerAttackBuilder &operator=(const PlayerAttackBuilder &);
  flatbuffers::Offset<PlayerAttack> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerAttack>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerAttack> CreatePlayerAttack(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  PlayerAttackBuilder builder_(_fbb);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlayerAttack> CreatePlayerAttackDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return GameMsg::CreatePlayerAttack(
      _fbb,
      name__);
}

struct PlayerSkill FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_TYPE = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  SkillType type() const {
    return static_cast<SkillType>(GetField<int8_t>(VT_TYPE, 0));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           verifier.EndTable();
  }
};

struct PlayerSkillBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(PlayerSkill::VT_NAME, name);
  }
  void add_type(SkillType type) {
    fbb_.AddElement<int8_t>(PlayerSkill::VT_TYPE, static_cast<int8_t>(type), 0);
  }
  explicit PlayerSkillBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PlayerSkillBuilder &operator=(const PlayerSkillBuilder &);
  flatbuffers::Offset<PlayerSkill> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerSkill>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerSkill> CreatePlayerSkill(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    SkillType type = SkillType_One) {
  PlayerSkillBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlayerSkill> CreatePlayerSkillDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    SkillType type = SkillType_One) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return GameMsg::CreatePlayerSkill(
      _fbb,
      name__,
      type);
}

struct PlayerExit FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct PlayerExitBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(PlayerExit::VT_NAME, name);
  }
  explicit PlayerExitBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PlayerExitBuilder &operator=(const PlayerExitBuilder &);
  flatbuffers::Offset<PlayerExit> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerExit>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerExit> CreatePlayerExit(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  PlayerExitBuilder builder_(_fbb);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlayerExit> CreatePlayerExitDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return GameMsg::CreatePlayerExit(
      _fbb,
      name__);
}

struct GameOver FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_WINCOLOR = 4
  };
  Color winColor() const {
    return static_cast<Color>(GetField<int8_t>(VT_WINCOLOR, 0));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_WINCOLOR) &&
           verifier.EndTable();
  }
};

struct GameOverBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_winColor(Color winColor) {
    fbb_.AddElement<int8_t>(GameOver::VT_WINCOLOR, static_cast<int8_t>(winColor), 0);
  }
  explicit GameOverBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  GameOverBuilder &operator=(const GameOverBuilder &);
  flatbuffers::Offset<GameOver> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GameOver>(end);
    return o;
  }
};

inline flatbuffers::Offset<GameOver> CreateGameOver(
    flatbuffers::FlatBufferBuilder &_fbb,
    Color winColor = Color_Red) {
  GameOverBuilder builder_(_fbb);
  builder_.add_winColor(winColor);
  return builder_.Finish();
}

struct Msg FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MSG = 4,
    VT_DATA_TYPE = 6,
    VT_DATA = 8
  };
  MsgType msg() const {
    return static_cast<MsgType>(GetField<int8_t>(VT_MSG, 0));
  }
  Date data_type() const {
    return static_cast<Date>(GetField<uint8_t>(VT_DATA_TYPE, 0));
  }
  const void *data() const {
    return GetPointer<const void *>(VT_DATA);
  }
  template<typename T> const T *data_as() const;
  const GameInit *data_as_gameInit() const {
    return data_type() == Date_gameInit ? static_cast<const GameInit *>(data()) : nullptr;
  }
  const PlayerMove *data_as_playerMove() const {
    return data_type() == Date_playerMove ? static_cast<const PlayerMove *>(data()) : nullptr;
  }
  const PlayerAttack *data_as_playerAttack() const {
    return data_type() == Date_playerAttack ? static_cast<const PlayerAttack *>(data()) : nullptr;
  }
  const PlayerSkill *data_as_playerSkill() const {
    return data_type() == Date_playerSkill ? static_cast<const PlayerSkill *>(data()) : nullptr;
  }
  const GameOver *data_as_gameOver() const {
    return data_type() == Date_gameOver ? static_cast<const GameOver *>(data()) : nullptr;
  }
  const PlayerExit *data_as_playerExit() const {
    return data_type() == Date_playerExit ? static_cast<const PlayerExit *>(data()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_MSG) &&
           VerifyField<uint8_t>(verifier, VT_DATA_TYPE) &&
           VerifyOffset(verifier, VT_DATA) &&
           VerifyDate(verifier, data(), data_type()) &&
           verifier.EndTable();
  }
};

template<> inline const GameInit *Msg::data_as<GameInit>() const {
  return data_as_gameInit();
}

template<> inline const PlayerMove *Msg::data_as<PlayerMove>() const {
  return data_as_playerMove();
}

template<> inline const PlayerAttack *Msg::data_as<PlayerAttack>() const {
  return data_as_playerAttack();
}

template<> inline const PlayerSkill *Msg::data_as<PlayerSkill>() const {
  return data_as_playerSkill();
}

template<> inline const GameOver *Msg::data_as<GameOver>() const {
  return data_as_gameOver();
}

template<> inline const PlayerExit *Msg::data_as<PlayerExit>() const {
  return data_as_playerExit();
}

struct MsgBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_msg(MsgType msg) {
    fbb_.AddElement<int8_t>(Msg::VT_MSG, static_cast<int8_t>(msg), 0);
  }
  void add_data_type(Date data_type) {
    fbb_.AddElement<uint8_t>(Msg::VT_DATA_TYPE, static_cast<uint8_t>(data_type), 0);
  }
  void add_data(flatbuffers::Offset<void> data) {
    fbb_.AddOffset(Msg::VT_DATA, data);
  }
  explicit MsgBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MsgBuilder &operator=(const MsgBuilder &);
  flatbuffers::Offset<Msg> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Msg>(end);
    return o;
  }
};

inline flatbuffers::Offset<Msg> CreateMsg(
    flatbuffers::FlatBufferBuilder &_fbb,
    MsgType msg = MsgType_MsgType_None,
    Date data_type = Date_NONE,
    flatbuffers::Offset<void> data = 0) {
  MsgBuilder builder_(_fbb);
  builder_.add_data(data);
  builder_.add_data_type(data_type);
  builder_.add_msg(msg);
  return builder_.Finish();
}

inline bool VerifyDate(flatbuffers::Verifier &verifier, const void *obj, Date type) {
  switch (type) {
    case Date_NONE: {
      return true;
    }
    case Date_gameInit: {
      auto ptr = reinterpret_cast<const GameInit *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Date_playerMove: {
      auto ptr = reinterpret_cast<const PlayerMove *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Date_playerAttack: {
      auto ptr = reinterpret_cast<const PlayerAttack *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Date_playerSkill: {
      auto ptr = reinterpret_cast<const PlayerSkill *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Date_gameOver: {
      auto ptr = reinterpret_cast<const GameOver *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Date_playerExit: {
      auto ptr = reinterpret_cast<const PlayerExit *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool VerifyDateVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyDate(
        verifier,  values->Get(i), types->GetEnum<Date>(i))) {
      return false;
    }
  }
  return true;
}

inline const GameMsg::Msg *GetMsg(const void *buf) {
  return flatbuffers::GetRoot<GameMsg::Msg>(buf);
}

inline const GameMsg::Msg *GetSizePrefixedMsg(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<GameMsg::Msg>(buf);
}

inline bool VerifyMsgBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<GameMsg::Msg>(nullptr);
}

inline bool VerifySizePrefixedMsgBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<GameMsg::Msg>(nullptr);
}

inline void FinishMsgBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<GameMsg::Msg> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedMsgBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<GameMsg::Msg> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace GameMsg

#endif  // FLATBUFFERS_GENERATED_GAMEMSG_GAMEMSG_H_
