#version 120 core

 in vec4 vert_pos;

uniform sampler2D texture;

uniform bool hasTexture;

uniform vec2 lightPos;

void main()
{
//fragment shader runs after vertex shader
	//ambient light
	vec4 ambient = vec4(0.02,0.02,0.5,1.0);


	//convert light to view coords

	vec2 light_tmp = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0,1)).xy;

	//Calculate the vector from light to pixel (make circular)

	vec2 lightToFrag = light_tmp - vert_pos.xy;
	lightToFrag.y = lightToFrag.y /1.7;

	//Length of the vector (distance)

	float vecLength = clamp(length(lightToFrag) * 2, 0, 1);

	//lookup pixel in the texture

	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	//multiply it by the color and lighting

	if(hasTexture == true)
	{
		//calculates the final color of the pixel (inert color * texture color * light modifier)
		// 1 - vecLength makes sense --> the longer the vector from source to pixel, the dimmer we want the lighting to be at that point!

		gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength,1-vecLength,1-vecLength,1),0,1));

	
	}else{
		gl_FragColor = gl_Color;
		
	}



}