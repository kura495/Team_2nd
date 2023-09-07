#include"Object3d.hlsli"

struct Material
{
    
    float32_t4 color; //���̐F
    int32_t enableLighting; //���C�g�̃t���O
    float32_t4x4 uvTransform; //uv��SRT
};
struct DirectionalLight
{
    float32_t4 color; //���C�g�̐F
    float32_t3 direction; //���C�g�̌���
    float intensity; //���C�g�̋P�x
};
ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);
struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float cos;
    
	//���C�e�B���O
    if (gMaterial.enableLighting != 0)
    { //Lighting����ꍇ
        if (gMaterial.enableLighting == harfLambert)
        {
            float NdotL = dot(normalize(input.normal), -gDirectionalLight.direction);
            cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
            output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;
            output.color.x += (cos * 0.5f);
            if (cos >= 0.2f)
            {
                output.color.x += (cos * 1.0f) + 0.3f;
                output.color.y += (cos * -1.0f) + 0.9f;
            }
            if (cos <= 0.4f)
            {
                output.color.y -= (cos * -1.0f) + 0.3f;
                output.color.z += (cos * 1.0f) + 0.3f;
            }
        }
        else if (gMaterial.enableLighting == Lambert)
        {
            cos = saturate(dot(normalize(input.normal), -gDirectionalLight.direction));
            output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;

                output.color.x += (cos * 1.0f) + 0.5f;
                output.color.y += (cos * -1.0f) + 1.0f;
                output.color.z += (cos * 1.0f) + 0.5f;
            
        }
    }
    else
    { //Lighting���Ȃ��ꍇ
        output.color = gMaterial.color * textureColor;
    }
    
    return output;
}