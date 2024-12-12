varying vec3 N;
varying vec3 v;

uniform sampler2D myTexture;
varying vec2 vTexCoord;

void SpotLight(in int i,in vec3 eye,in vec3 ecPosition3,in vec3 normal,inout vec4 ambient,inout vec4 diffuse,inout vec4 specular)
{
/* normal . light direction */
    float nDotVP;           
/* normal . light half vector */
    float nDotHV;           
/* power factor */
    float pf;               
/* cosine of angle between spotlight*/
    float spotDot;          
/* spotlight attenuation factor*/
    float spotAttenuation;  
/* computed attenuation factor*/
    float attenuation;      
/* distance from surface to light source*/
    float d;                
/* direction from surface to light position*/
    vec3 VP;                
/* direction of maximum highlights*/
    vec3 halfVector;        

/* Compute vector from surface to light position*/
    VP = vec3(gl_LightSource[i].position) - ecPosition3;

/* Compute distance between surface and light position*/
    d = length(VP);

/* Normalize the vector from surface to light position */
    VP = normalize(VP);

/* Compute attenuation */
    attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
                         gl_LightSource[i].linearAttenuation * d +
                         gl_LightSource[i].quadraticAttenuation * d * d);

/* See if point on surface is inside cone of illumination */
    spotDot = dot(-VP, normalize(gl_LightSource[i].spotDirection));

    if (spotDot < gl_LightSource[i].spotCosCutoff)
/* light adds no contribution */
        spotAttenuation = 0.0; 
    else
        spotAttenuation = pow(spotDot, gl_LightSource[i].spotExponent);

/* Combine the spotlight and distance attenuation. */
    attenuation *= spotAttenuation;

    halfVector = normalize(VP + eye);

    nDotVP = max(0.0, dot(normal, VP));
    nDotHV = max(0.0, dot(normal, halfVector));

    if (nDotVP == 0.0)
        pf = 0.0;
    else
        pf = pow(nDotHV, gl_FrontMaterial.shininess);

    ambient  += gl_LightSource[i].ambient * attenuation;
    diffuse  += gl_LightSource[i].diffuse * nDotVP * attenuation;
    specular += gl_LightSource[i].specular * pf * attenuation;
}


void main()
{
    float intensity;
    vec3 n;
    vec4 color;
    vec4 amb  = vec4(0.0);
    vec4 diff  = vec4(0.0);
    vec4 spec = vec4(0.0);
   
/* vertex to eye coordinates*/
    vec4 ecPosition  = vec4(v,1.0);
/* in 3 space*/
    vec3 ecPosition3 = v;

    vec3 eye = -normalize(ecPosition3);

/* Compute addition from single spotlight in scene.
   Limited to local viewer !!!
   Directional light, pointlight must be computed differently...*/

    SpotLight(0, eye, ecPosition3, N, amb, diff, spec);

/* more that one light
for (i = 0; i < NumEnabledLights; i++)
    SpotLight(i, eye, ecPosition3, N, amb, diff, spec);
*/


    color = gl_FrontMaterial.ambient * gl_LightModel.ambient +
            gl_FrontMaterial.emission + 
            amb * gl_FrontMaterial.ambient + diff * gl_FrontMaterial.diffuse + spec * gl_FrontMaterial.specular;


/*
fog = exp(-gl_Fog.density * gl_Fog.density * gl_FogFragCoord * gl_FogFragCoord);
fog = clamp(fog, 0.0, 1.0);
color = mix(vec3(gl_Fog.color), color, fog);
*/

/* MODULATE texture, inaccurate (specular should be separate) */
    gl_FragColor = texture2D(myTexture, vTexCoord.xy) * color;
}
