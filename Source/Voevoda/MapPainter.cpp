#include "MapPainter.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "PaperTileMap.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"

void AMapPainter::ImportTileSets() {
    //Base terrain types:
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
    static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetArmy(
        TEXT("PaperTileSet'/Game/texture/warriortileset'"));
    if (TileSetAssetArmy.Succeeded()) {
        ArmyTileSet = TileSetAssetArmy.Object;
    }
    static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetCastle(
        TEXT("PaperTileSet'/Game/texture/castletileset'"));
    if (TileSetAssetCastle.Succeeded()) {
        CastleTileSet = TileSetAssetCastle.Object;
    }
    static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetCity(
        TEXT("PaperTileSet'/Game/texture/citytileset'"));
    if (TileSetAssetCastle.Succeeded()) {
        CityTileSet = TileSetAssetCastle.Object;
    }

    //Dark terrain types:
    static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetDarkCastle(
        TEXT("PaperTileSet'/Game/texture/Dark/DarkCastleTileSet'"));
    if (TileSetAssetDarkCastle.Succeeded()) {
        DarkCastleTileSet = TileSetAssetDarkCastle.Object;
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

AMapPainter::AMapPainter() {

    PrimaryActorTick.bCanEverTick = true;

    ImportTileSets();

}


void AMapPainter::Tick(float DeltaTime) {
    FVector PlayerLocation = GetWorld()
        ->GetFirstPlayerController()
        ->GetPawn()
        ->GetActorLocation(); // works only from Tick()
    int32 moveX = (static_cast<int>(PlayerLocation.X) - InitPlayerX);
    int32 moveY = (static_cast<int>(PlayerLocation.Y) - InitPlayerY);
    int32 defaultX = 0; // based on character init coordinates
    int32 defaultY = 0;
    int32 Tile_X = abs(
        ((defaultX + moveX) / TileMapComponent->TileMap->TileWidth) % map.Width);
    int32 Tile_Y =
        abs(((defaultY - moveY) / TileMapComponent->TileMap->TileHeight) %
            map.Height); // very easy swap Height and Width
    UpdateRhombVision(Tile_X, Tile_Y, 7, VisionType::Unseen);
    UpdateRhombVision(Tile_X, Tile_Y, 5, VisionType::Seen);
    Super::Tick(DeltaTime);
}
void AMapPainter::UpdateRhombVision(
    int32 X, int32 Y,
    int32 Radius, VisionType vision) { // takes correct X, Y, UpdateTileVision() with uncorrect
    for (int i = 0; i <= Radius; i++) {
        for (int j = 0; j <= Radius - i; j++) {
            UpdateTileVision(X + i, Y + j, vision);
        }
    }
    for (int i = 0; i >= -Radius; i--) {
        for (int j = 0; j >= -i - Radius; j--) {
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

void AMapPainter::UpdateTileVision(int32 X, int32 Y, VisionType vision) {
    X = abs((X) % map.Width);
    Y = abs((Y) % map.Height);
    FPaperTileInfo TileInfo;
    switch (map.TerrainData[X][Y]) {
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
    case Army_position:
        if (vision == VisionType::Seen) {
            TileInfo.TileSet = ArmyTileSet;
        }
        else {
            TileInfo.TileSet = DarkGrassTileSet;
        }
        break;
    case Castle:
        if (vision == VisionType::Seen) {
            TileInfo.TileSet = CastleTileSet;
        }
        else {
            TileInfo.TileSet = DarkCastleTileSet;
        }
        break;
    }
    TileInfo.PackedTileIndex = 0;
    TileMapComponent->SetTile(X, Y, 0, TileInfo);
}

void AMapPainter::BeginPlay() {
    Super::BeginPlay();

   // BeginPlayFunction();

 /*   for (TActorIterator<APaperTileMapActor> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {

        TileMapComponent = ActorItr->GetRenderComponent();
    }

    if (TileMapComponent) {
        generate_map();
        TileMapComponent->ResizeMap(map.Width, map.Height);
        FVector PlayerLocation =
            GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        InitPlayerX = static_cast<int>(PlayerLocation.X);
        InitPlayerY = static_cast<int>(PlayerLocation.Y);
        OneColorMap();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("TileMapComponent is nullptr."));
    }*/
}

void AMapPainter::BeginPlayFunction() {
    for (TActorIterator<APaperTileMapActor> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {

        TileMapComponent = ActorItr->GetRenderComponent();
    }

    if (TileMapComponent) {
        generate_map();
        TileMapComponent->ResizeMap(map.Width, map.Height);
        FVector PlayerLocation =
            GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        InitPlayerX = static_cast<int>(PlayerLocation.X);
        InitPlayerY = static_cast<int>(PlayerLocation.Y);
        OneColorMap();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("TileMapComponent is nullptr."));
    }
}

void AMapPainter::OneColorMap() {
    for (int32 X = 0; X < map.Width; ++X) {
        for (int32 Y = 0; Y < map.Height; ++Y) {
            FPaperTileInfo TileInfo;
            TileInfo.TileSet = FogTileSet;
            TileInfo.PackedTileIndex = 0;
            TileMapComponent->SetTile(X, Y, 0, TileInfo);
        }
    }
}
void AMapPainter::generate_map() {
    FString message = FString::Printf(TEXT("generate_map()"));
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
    map.random_generate();
    map.generate_enemies();
    //map.generate_cities();
}

int32 AMapPainter::GetMapTileHeight() {
    return TileMapComponent->TileMap->TileHeight;
}
int32 AMapPainter::GetMapTileWidth() {
    return TileMapComponent->TileMap->TileWidth;
}
int32 AMapPainter::GetInitPlayerY() {
    return InitPlayerY;
}
int32 AMapPainter::GetInitPlayerX() {
    return InitPlayerX;
}
