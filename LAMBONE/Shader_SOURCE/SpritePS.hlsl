#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

//Texture2D albedoTexture : register(t0);
//SamplerState pointSampler : register(s0);
//SamplerState anisotropicSampler : register(s1);

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float)0.0f;

    // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200
    color = albedoTexture.Sample(anisotropicSampler, In.UV);

    //if (color.a <= 0.0f)
    //    discard;

    //if (animationType == 1)
    //{
    //    float2 diff = (AtlasSize - SpriteSize) / 2.0f;
    //    float2 UV = (SpriteLeftTop - diff - SpriteOffset)
    //        + (AtlasSize * In.UV);

    //    if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
    //        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
    //        discard;

    //    color = atlasTexture.Sample(anisotropicSampler, UV);
    //}

    //color *= lightsAttribute[0].color;

    /*
        Ambient Light(간접광) 처리를 위하여
        전부 0으로 처리하지 않고 값을 넣어줌.

        float4 lightColor = (float4) 0.0f;
        위와 같이 처리시,
        조명이 하나도 없을 경우
        오브젝트가 보이지 않는다.
    */
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);

    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }

    color *= lightColor;

    return color;
}