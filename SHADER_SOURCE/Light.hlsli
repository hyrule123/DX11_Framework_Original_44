#include "ConstantBuffer.hlsli"


struct LightColor
{
    float4 diffuse;
    float4 specular;
    float4 ambient;
};

struct LightAttribute
{
    LightColor color;
    float4 position;
    float4 direction;
    
    int type;
    float radius;
    float angle;
    int padding;
};

StructuredBuffer<LightAttribute> lightAttributes : register(t13);
//StructuredBuffer<LightAttribute> lightAttributes3D : register(t14);

//2D
void CalculateLight(in out LightColor pLightColor, float3 position, int idx)
{
    if (0 == lightAttributes[idx].type)
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse;
    }
    else if (1 == lightAttributes[idx].type)
    {
        float length = distance(lightAttributes[idx].position.xy, position.xy);
        
        if (length < lightAttributes[idx].radius)
        {
            float ratio = 1.0f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio;
        }
        
    }
    else
    {
        
    }
}

//3D
static float3 globalLightPos = float3(0.0f, 0.0f, 0.0f);
static float3 globalLightDir = float3(1.0f, -1.0f, 1.0f);
static float3 globalLightColor = float3(1.0f, 1.0f, 1.0f);
static float3 globalLightAmb = float3(0.15f, 0.15f, 0.15f);

void CalculateLight3D(float3 viewPos, float3 viewNormal, int lightIdx, inout LightColor lightColor)
{
    
   
    LightAttribute lightInfo = lightAttributes[lightIdx];
    
    float3 viewLightDir = (float3) 0.0f;

        //view space �󿡼� ���� ���⸦ ����
    float fDiffPow = 0.0f;
    float fSpecPow = 0.0f;
    
    // Directional
    if (0 == lightInfo.type)
    {
        viewLightDir = normalize(mul(float4(lightInfo.direction.xyz, 0.0f), view));

        //view space �󿡼� ���� ���⸦ ����
        fDiffPow = saturate(dot(-viewLightDir, viewNormal));
        fSpecPow = 0.0f;
        
        // �ݻ籤 ���⸦ ����
        // ǥ���� ���� �ݻ纤��
        float3 viewReflect = normalize(viewLightDir + 2.0f * dot(-viewLightDir, viewNormal) * viewNormal);
        
        // �������� ǥ���� ���ϴ� ����
        float3 vEye = normalize(viewPos);
    
        //�ü� ���Ͷ� �ݻ纤�͸� �����ؼ� �ݻ籤�� ���⸦ ���Ѵ�.
        fSpecPow = saturate(dot(-vEye, viewReflect));
        fSpecPow = pow(fSpecPow, 30);
        

    }
    // point
    else if (1 == lightInfo.type)
    {
        // view space �󿡼� ������ ��ġ�� �˾Ƴ���.
        float3 vLightViewPos = mul(float4(lightInfo.position.xyz, 1.0f), view);
        
        // ������ ��ġ���� ǥ���� ���ϴ� ����
        viewLightDir = viewPos - vLightViewPos;
        
        //�������� ǥ������� �Ÿ��� ���Ѵ�.
        float dist = length(viewLightDir);
        
        // �������� ǥ���� ���ϴ� �������͸� ���Ѵ�.
        viewLightDir = normalize(viewLightDir);
        
        // �ݰ��� �Ÿ��� ���� ���� ���� ����
        float ratio = cos(saturate(dist / lightInfo.radius) * 3.1415926535 * 0.5f);
        
        //view space �󿡼� ǥ���� ���� ���⸦ ����
        fDiffPow = saturate(dot(-viewLightDir, viewNormal)) * ratio;
        
        // �ݻ籤�� ���⸦ ����
        // ǥ���� ���� �ݻ纤��
        float3 viewReflect = normalize(viewLightDir + 2.0f * dot(-viewLightDir, viewNormal) * viewNormal);
        
        // �������� ǥ���� ���ϴ� ����
        float3 vEye = normalize(viewPos);
        
        //�ü� ���Ͷ� �ݻ纤�͸� �����ؼ� �ݻ籤�� ���⸦ ���Ѵ�.
        fSpecPow = saturate(dot(-vEye, viewReflect));
        fSpecPow = pow(fSpecPow, 30);
    }
    else
    {
        
    }
    
    // ���� ���ݻ籤
    lightColor.diffuse += lightInfo.color.diffuse * fDiffPow;
        
        // ���ݻ籤
    lightColor.specular += lightInfo.color.specular * fSpecPow;
        
        // �ֺ���
    lightColor.ambient = lightInfo.color.ambient;
}

//void CalculateLight3D(float3 _vViewPos, float3 _vViewNormal, int _LightIdx, inout LightColor _lightcolor)
//{
//    LightAttribute lightinfo = lightAttributes[_LightIdx];
       
//    float3 ViewLightDir = (float3) 0.f;
//    float fDiffPow = (float) 0.f;
//    float fSpecPow = (float) 0.f;
    
//    // Directional Light
//    if (lightinfo.type == 0)
//    {
//        ViewLightDir = normalize(mul(float4(lightinfo.direction.xyz, 0.f), view));
    
//        // View �����̽� �󿡼� ǥ���� ���� ���⸦ ����
//        fDiffPow = saturate(dot(-ViewLightDir, _vViewNormal));
    
//        // �ݻ籤 ���⸦ ����
//        // ǥ���� ���� �ݻ纤��       
//        float3 vViewReflect = normalize(ViewLightDir + 2.f * dot(-ViewLightDir, _vViewNormal) * _vViewNormal);
        
//        // �������� ǥ���� ���ϴ� ����
//        float3 vEye = normalize(_vViewPos);
        
//        // �ü� ���Ϳ� �ݻ纤�͸� �����ؼ� �ݻ籤�� ���⸦ ����
//        fSpecPow = saturate(dot(-vEye, vViewReflect));
//        fSpecPow = pow(fSpecPow, 20);
//    }
    
//    // Point Light
//    else if (lightinfo.type == 1)
//    {
//        // ViewSpace �󿡼� ������ ��ġ�� �˾Ƴ���.
//        float3 vLightViewPos = mul(float4(lightinfo.position.xyz, 1.f), view);
        
//        // ������ ��ġ���� ǥ���� ���ϴ� ���͸� ���Ѵ�.
//        ViewLightDir = _vViewPos - vLightViewPos;
        
//        // �������� ǥ������� �Ÿ��� ���Ѵ�.
//        float fDist = length(ViewLightDir);
        
//        // �������� ǥ���� ���ϴ� �������͸� ���Ѵ�.        
//        ViewLightDir = normalize(ViewLightDir);
        
//        // �ݰ��� �Ÿ��� ���� ���� ���� ����
//        //float fRatio = saturate(1.f - (fDist / lightinfo.fRadius));        
//        float fRatio = cos(saturate(fDist / lightinfo.radius) * 3.1415926535f * 0.5f);
                        
//        // View �����̽� �󿡼� ǥ���� ���� ���⸦ ����        
//        fDiffPow = saturate(dot(-ViewLightDir, _vViewNormal)) * fRatio;

//        // �ݻ籤 ���⸦ ����
//        // ǥ���� ���� �ݻ纤��       
//        float3 vViewReflect = normalize(ViewLightDir + 2.f * dot(-ViewLightDir, _vViewNormal) * _vViewNormal);
        
//        // �������� ǥ���� ���ϴ� ����
//        float3 vEye = normalize(_vViewPos);
        
//        // �ü� ���Ϳ� �ݻ纤�͸� �����ؼ� �ݻ籤�� ���⸦ ����
//        fSpecPow = saturate(dot(-vEye, vViewReflect));
//        fSpecPow = pow(fSpecPow, 20);
//    }
    
//    // SpotLight
//    else
//    {
        
//    }
    
//    // ���� ���ݻ籤
//    _lightcolor.diffuse += lightinfo.color.diffuse * fDiffPow;
    
//    // ���� �ݻ籤 
//    _lightcolor.specular += lightinfo.color.specular * fSpecPow;

//    // ���� ȯ�汤
//    _lightcolor.ambient += lightinfo.color.ambient;
//}
