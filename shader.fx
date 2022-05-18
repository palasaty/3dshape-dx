cbuffer ConstantBuffer
{
    matrix World;
    matrix View;
    matrix Projection;
}

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
    float4 Color : COLOR0;
};


VS_OUTPUT VS( float4 Pos : POSITION, float3 Norm : NORMAL, float4 Color : COLOR )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Norm = mul(Norm, World);
    output.Color = Color;
    return output;
}



float4 PS( VS_OUTPUT input ) : SV_Target
{
    return float4(1, 0, 0, 0);
}