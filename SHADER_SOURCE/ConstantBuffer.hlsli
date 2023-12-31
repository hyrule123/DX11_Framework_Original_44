cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix inverseWorld;
    row_major matrix view;
    row_major matrix inverseView;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    uint usedAlbedo;
    uint usedNormal;
    uint usedSpecular;
    uint padd2;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer Animation : register(b3)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}

cbuffer NumberOfLight : register(b4)
{
    uint numberOfLight;
    uint indexOfLight;
}

cbuffer ParticleSystem : register(b5)
{
    float4 worldPosition;
    float4 startColor;
    float4 startSize;
    
    uint maxParticles;
    uint simulationSpace;
    float radius;
    float startSpeed;
    
    float startLifeTime;
    float deltaTime;
    float elapsedTime; //�����ð�
    int padding;
}

//cbuffer Noise : register(b6)
//{
//    float4 NoiseSize;
//}