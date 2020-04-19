package com.mygdx.game;

import Effekseer.swig.EffekseerManagerCore;
import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import Effekseer.swig.*;

import java.io.Console;
import java.io.File;

public class libGdxSample extends ApplicationAdapter {
	SpriteBatch batch;
	Texture img;
	EffekseerManagerCore effekseerManagerCore;
	EffekseerEffectCore effekseerEffectCore;

	@Override
	public void create () {
		batch = new SpriteBatch();
		img = new Texture("badlogic.jpg");

		System.loadLibrary("EffekseerNativeForJava");

		EffekseerBackendCore.InitializeAsOpenGL();

		effekseerManagerCore = new EffekseerManagerCore();
		effekseerManagerCore.Initialize(8000);

		String effectPath = "Laser01.efkefc";
		com.badlogic.gdx.files.FileHandle handle = Gdx.files.internal(effectPath );
		effekseerEffectCore = new EffekseerEffectCore();
		byte[] bytes = handle.readBytes();
		if(!effekseerEffectCore.Load(bytes, bytes.length, 50.0f))
		{
			System.out.print("Failed to load.");
		}

		// load textures
		for(int i = 0; i < effekseerEffectCore.GetTextureCount(EffekseerTextureType.Color); i++)
		{
			String path = (new File(effectPath)).getParent();
			if(path != null)
			{
				path += "/" + effekseerEffectCore.GetTexturePath(i, EffekseerTextureType.Color);
			}
			else
			{
				path = effekseerEffectCore.GetTexturePath(i, EffekseerTextureType.Color);
			}

			handle = Gdx.files.internal(path);
			bytes = handle.readBytes();
			effekseerEffectCore.LoadTexture(bytes, bytes.length, i, EffekseerTextureType.Color);
		}

		// TODO
		// EffekseerTextureType.Normal
		// EffekseerTextureType.Distortion

		int efkhandle = effekseerManagerCore.Play(effekseerEffectCore);
		effekseerManagerCore.SetEffectPosition(efkhandle,
				Gdx.graphics.getWidth() / 2.0f,Gdx.graphics.getHeight() / 2.0f, 0.0f);
	}

	@Override
	public void render () {
		Gdx.gl.glClearColor(0, 0, 0, 1);
		// It needs to clear depth
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
		//batch.begin();
		//batch.draw(img, 0, 0);
		//batch.end();
		
		effekseerManagerCore.SetViewProjectionMatrixWithSimpleWindow(Gdx.graphics.getWidth(),Gdx.graphics.getHeight());
		effekseerManagerCore.Update(Gdx.graphics.getDeltaTime() / (1.0f / 60.0f));
		effekseerManagerCore.DrawBack();
		effekseerManagerCore.DrawFront();
	}
	
	@Override
	public void dispose () {
		batch.dispose();
		img.dispose();
		effekseerManagerCore.delete();
		effekseerEffectCore.delete();
		EffekseerBackendCore.Terminate();
	}
}
