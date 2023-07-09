#include "globals.hlsli"

//structedBuffer
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

//cbuffer Transform : register(b0)
//{
//    row_major matrix mWorld;
//    row_major matrix mView;
//    row_major matrix mProjection;
//}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.0f;

    //ut.Pos = float4(In.Pos, 1.0f);
    //Out.Pos.x += 0.4f; //inputPosX; -> ������۸� ���ؼ� �� �����Ͱ� �ѿ;��Ѵ�.
    //Out.Pos.x += Position.x;
    //Out.Pos.y += Position.y;

    float4 world = mul(float4(In.Pos, 1.0f), WorldMatrix);
    float4 view = mul(world, ViewMatrix);
    float4 proj = mul(view, ProjectionMatrix);
    
    Out.Pos = proj;
    Out.UV = In.UV;
    Out.Color = In.Color;

    return Out;
}