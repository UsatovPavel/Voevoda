#include "MapGenerator.h"
#include "PaperTileMap.h"
#include "PaperTileMapActor.h"
#include "EngineUtils.h"
#include "PaperTileMapComponent.h"


void AMapGenerator::ImportTileSets() {
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetGrass(TEXT("PaperTileSet'/Game/texture/grasstileset'"));
	if (TileSetAssetGrass.Succeeded())
	{
		GrassTileSet = TileSetAssetGrass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetWater(TEXT("PaperTileSet'/Game/texture/watertileset'"));
	if (TileSetAssetWater.Succeeded())
	{
		WaterTileSet = TileSetAssetWater.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetWoods(TEXT("PaperTileSet'/Game/texture/woodstileset'"));
	if (TileSetAssetWoods.Succeeded())
	{
		WoodsTileSet = TileSetAssetWoods.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TileSetAssetMountains(TEXT("PaperTileSet'/Game/texture/mountainstileset'"));
	if (TileSetAssetMountains.Succeeded())
	{
		MountainsTileSet = TileSetAssetMountains.Object;
	}
}

AMapGenerator::AMapGenerator() {

	PrimaryActorTick.bCanEverTick = true;

	ImportTileSets();

	MapHeight = FMath::RandRange(100, 500);
	MapWidth = FMath::RandRange(100, 500);

}

void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<APaperTileMapActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		
			TileMapComponent = ActorItr->GetRenderComponent();

	}

	if (TileMapComponent)
	{
		TileMapComponent->ResizeMap(MapWidth, MapHeight);
		GenerateTileMap();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TileMapComponent is nullptr."));
	}
}

void AMapGenerator::GenerateTileMap()
{

		for (int32 X = 0; X < MapWidth; ++X)
		{
			for (int32 Y = 0; Y < MapHeight; ++Y)
			{
				FPaperTileInfo TileInfo;

				//int32 Scale1 = FMath::RandRange(0, 5)+X;
				//int32 Scale2 = FMath::RandRange(0, 5)+Y;


				int32 Scale1 = X;
				int32 Scale2 = Y;

				float NoiseValue = FMath::PerlinNoise2D(FVector2D(Scale1 /15.0f, Scale2 / 15.0f));
				NoiseValue = (NoiseValue + 1.0f) / 2.0f;

				if (NoiseValue < 0.2f)
				{
					TileInfo.TileSet = MountainsTileSet;
					TileInfo.PackedTileIndex = 0;
				}
				else if (NoiseValue < 0.25f)
				{
					TileInfo.TileSet = GrassTileSet;
					TileInfo.PackedTileIndex = 0;
				}
				else if (NoiseValue < 0.35f)
				{
					TileInfo.TileSet = WoodsTileSet;
					TileInfo.PackedTileIndex = 0;
				}
				else if (NoiseValue < 0.45f)
				{
					TileInfo.TileSet = GrassTileSet;
					TileInfo.PackedTileIndex = 0;
				}
				else if (NoiseValue < 0.50f)
				{
					TileInfo.TileSet = WaterTileSet;
					TileInfo.PackedTileIndex = 0;
				}
				else
				{
					TileInfo.TileSet = GrassTileSet;
					TileInfo.PackedTileIndex = 0;
				}
				TileMapComponent->SetTile(X, Y, 0, TileInfo);

			}
	
		}
}

