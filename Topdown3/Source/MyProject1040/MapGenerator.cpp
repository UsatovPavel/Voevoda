#include "MapGenerator.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "PaperTileMap.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"

int GetX_PlayerTile() {
  // FVector PlayerLocation =
  // GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(); ��
  // ����� �� GetWorld
  int32 p = 0;
  return p;
}
void AMapGenerator::ImportTileSets() {
  static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetGrass(
      TEXT("PaperTileSet'/Game/texture/grasstileset'"));
  if (TileSetAssetGrass.Succeeded()) {
    GrassTileSet = TileSetAssetGrass.Object;
  }
  static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetWater(
      TEXT("PaperTileSet'/Game/texture/watertileset'"));
  if (TileSetAssetWater.Succeeded()) {
    WaterTileSet = TileSetAssetWater.Object;
  }
  static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetWoods(
      TEXT("PaperTileSet'/Game/texture/WhiteWoodTileSet'"));
  if (TileSetAssetWoods.Succeeded()) {
    WoodsTileSet = TileSetAssetWoods.Object;
  }
  static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetMountains(
      TEXT("PaperTileSet'/Game/texture/mountainstileset'"));
  if (TileSetAssetMountains.Succeeded()) {
    MountainsTileSet = TileSetAssetMountains.Object;
  }

  static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetFog(
      TEXT("PaperTileSet'/Game/texture/fogtileset'"));
  if (TileSetAssetFog.Succeeded()) {
    FogTileSet = TileSetAssetFog.Object;
  }


    static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetDarkGrass(
      TEXT("PaperTileSet'/Game/texture/Dark/DarkGrassTileSet'"));
  if (TileSetAssetDarkGrass.Succeeded()) {
    DarkGrassTileSet = TileSetAssetDarkGrass.Object;
  }
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetDarkWood(
      TEXT("PaperTileSet'/Game/texture/Dark/DarkWoodsTileSet'"));
  if (TileSetAssetDarkWood.Succeeded()) {
    DarkWoodsTileSet = TileSetAssetDarkWood.Object;
  }
      static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetDarkWater(
      TEXT("PaperTileSet'/Game/texture/Dark/DarkWaterTileSet'"));
  if (TileSetAssetDarkWater.Succeeded()) {
    DarkWaterTileSet = TileSetAssetDarkWater.Object;
  }
      static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetDarkMountains(
      TEXT("PaperTileSet'/Game/texture/Dark/DarkMountainsTileSet'"));
  if (TileSetAssetDarkMountains.Succeeded()) {
    DarkMountainsTileSet = TileSetAssetDarkMountains.Object;
  }

}

AMapGenerator::AMapGenerator() {

  PrimaryActorTick.bCanEverTick = true;

  ImportTileSets();

  MapHeight = FMath::RandRange(100, 500);
  MapWidth = FMath::RandRange(100, 500);
}

void AMapGenerator::Tick(float DeltaTime) {
  FVector PlayerLocation = GetWorld()
                               ->GetFirstPlayerController()
                               ->GetPawn()
                               ->GetActorLocation(); // works only from Tick()
  int32 moveX = (static_cast<int>(PlayerLocation.X) - InitPlayerX);
  int32 moveY = (static_cast<int>(PlayerLocation.Y) - InitPlayerY);
  int32 defaultX = 0; // based on character init coordinates
  int32 defaultY = 0;
  int32 Tile_X = abs(
      ((defaultX + moveX) / TileMapComponent->TileMap->TileWidth) % MapWidth);
  int32 Tile_Y =
      abs(((defaultY - moveY) / TileMapComponent->TileMap->TileHeight) %
          MapHeight); // very easy swap Height and Width
  UpdateRhombVision(Tile_X, Tile_Y, 7, VisionType::Unseen);
  UpdateRhombVision(Tile_X, Tile_Y, 5, VisionType::Seen);
  Super::Tick(DeltaTime);
}
void AMapGenerator::UpdateRhombVision(
    int32 X, int32 Y,
    int32 Radius, VisionType vision) { // takes correct X, Y, UpdateTileVision() with uncorrect
  for (int i = 0; i <= Radius; i++) {
    for (int j = 0; j <= Radius - i; j++) {
      UpdateTileVision(X + i, Y + j, vision);
    }
  }
  for (int i = 0; i >= -Radius; i--) {
    for (int j = 0; j >= -i-Radius; j--) {
      UpdateTileVision(X + i, Y + j, vision);
    }
  }
  for (int i = 0; i >= -Radius; i--) {
    for (int j = 0; j <= Radius + i; j++) {
      UpdateTileVision(X + i, Y + j, vision);
    }
  }
  for (int j = 0; j >= -Radius; j--) {
    for (int i = 0; i <= Radius + j; i++) {
      UpdateTileVision(X + i, Y + j, vision);
    }
  }
}

void AMapGenerator::UpdateTileVision(int32 X, int32 Y, VisionType vision) {
  X = abs((X) % MapWidth); // safe pass
  Y = abs((Y) % MapHeight);
  FPaperTileInfo TileInfo;
  switch (TerrainData[X][Y]) {
  case Grass:
      if (vision == VisionType::Seen) {
          TileInfo.TileSet = GrassTileSet;
      }
      else {
          TileInfo.TileSet = DarkGrassTileSet;
      }
    break;
  case Woods:
    	if (vision == VisionType::Seen) {
          TileInfo.TileSet = WoodsTileSet;
      }
      else {
          TileInfo.TileSet = DarkWoodsTileSet;
      }
    break;
  case Mountains:
        	if (vision == VisionType::Seen) {
          TileInfo.TileSet = MountainsTileSet;
      }
      else {
          TileInfo.TileSet = DarkMountainsTileSet;
      }
    break;
  case Water:
            	if (vision == VisionType::Seen) {
          TileInfo.TileSet = WaterTileSet;
      }
      else {
          TileInfo.TileSet = DarkWaterTileSet;
      }
    break;
  }
  TileInfo.PackedTileIndex = 0;
  TileMapComponent->SetTile(X, Y, 0, TileInfo);
}

void AMapGenerator::BeginPlay() {
  Super::BeginPlay();

  for (TActorIterator<APaperTileMapActor> ActorItr(GetWorld()); ActorItr;
       ++ActorItr) {

    TileMapComponent = ActorItr->GetRenderComponent();
  }

  if (TileMapComponent) {
    InitTerrainData();
    GenerateTerrainData();
    TileMapComponent->ResizeMap(MapWidth, MapHeight);
    FVector PlayerLocation =
        GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    InitPlayerX = static_cast<int>(PlayerLocation.X);
    InitPlayerY = static_cast<int>(PlayerLocation.Y);
    OneColorMap();
  } else {
    UE_LOG(LogTemp, Warning, TEXT("TileMapComponent is nullptr."));
  }
}

void AMapGenerator::OneColorMap() {
  for (int32 X = 0; X < MapWidth; ++X) {
    for (int32 Y = 0; Y < MapHeight; ++Y) {
      FPaperTileInfo TileInfo;

      int32 Scale1 = X;
      int32 Scale2 = Y;
      TileInfo.TileSet = FogTileSet;
      TileInfo.PackedTileIndex = 0;
      TileMapComponent->SetTile(X, Y, 0, TileInfo);
    }
  }
}

void AMapGenerator::InitTerrainData() { // how Init another way?
  TArray<TerrainType> DefaultStrip;
  DefaultStrip.Init(Grass, MapHeight);
  TerrainData.Init(DefaultStrip, MapWidth);
  // �� ������� ��� ����� -  �����
}

void AMapGenerator::GenerateTerrainData() {
  for (int32 X = 0; X < MapWidth; ++X) {
    for (int32 Y = 0; Y < MapHeight; ++Y) {
      int32 Scale1 = X;
      int32 Scale2 = Y;
      float NoiseValue =
          FMath::PerlinNoise2D(FVector2D(Scale1 / 15.0f, Scale2 / 15.0f));
      NoiseValue = (NoiseValue + 1.0f) / 2.0f;
      if (NoiseValue < 0.2f) {
        TerrainData[X][Y] = Mountains;
      } else if (NoiseValue < 0.25f) {
        TerrainData[X][Y] = Grass;
      } else if (NoiseValue < 0.35f) {
        TerrainData[X][Y] = Woods;
      } else if (NoiseValue < 0.45f) {
        TerrainData[X][Y] = Grass;
      } else if (NoiseValue < 0.50f) {
        TerrainData[X][Y] = Water;
      } else {
        TerrainData[X][Y] = Grass;
      }
    }
  }
}

void AMapGenerator::GenerateTileMap() {

  for (int32 X = 0; X < MapWidth; ++X) {
    for (int32 Y = 0; Y < MapHeight; ++Y) {
      FPaperTileInfo TileInfo;

      // int32 Scale1 = FMath::RandRange(0, 5)+X;
      // int32 Scale2 = FMath::RandRange(0, 5)+Y;

      int32 Scale1 = X;
      int32 Scale2 = Y;

      float NoiseValue =
          FMath::PerlinNoise2D(FVector2D(Scale1 / 15.0f, Scale2 / 15.0f));
      NoiseValue = (NoiseValue + 1.0f) / 2.0f;

      if (NoiseValue < 0.2f) {
        TileInfo.TileSet = MountainsTileSet;
        TileInfo.PackedTileIndex = 0;
      } else if (NoiseValue < 0.25f) {
        TileInfo.TileSet = GrassTileSet;
        TileInfo.PackedTileIndex = 0;
      } else if (NoiseValue < 0.35f) {
        TileInfo.TileSet = WoodsTileSet;
        TileInfo.PackedTileIndex = 0;
      } else if (NoiseValue < 0.45f) {
        TileInfo.TileSet = GrassTileSet;
        TileInfo.PackedTileIndex = 0;
      } else if (NoiseValue < 0.50f) {
        TileInfo.TileSet = WaterTileSet;
        TileInfo.PackedTileIndex = 0;
      } else {
        TileInfo.TileSet = GrassTileSet;
        TileInfo.PackedTileIndex = 0;
      }
      TileMapComponent->SetTile(X, Y, 0, TileInfo);
    }
  }
}
