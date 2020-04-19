package com.mygdx.game;

import Effekseer.swig.EffekseerManagerCore;
import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import Effekseer.swig.*;

import java.io.Console;

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

		com.badlogic.gdx.files.FileHandle handle = Gdx.files.internal("Simple.efkefc");
		effekseerEffectCore = new EffekseerEffectCore();
		byte[] bytes = handle.readBytes();
		if(!effekseerEffectCore.Load(bytes, bytes.length, 50.0f))
		{
			System.out.print("Failed to load.");
		}

		int efkhandle = effekseerManagerCore.Play(effekseerEffectCore);
		System.out.print(efkhandle);
	}

	@Override
	public void render () {
		Gdx.gl.glClearColor(0, 0, 0, 1);
		// It needs to clear depth
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
		//batch.begin();
		//batch.draw(img, 0, 0);
		//batch.end();
		
		effekseerManagerCore.SetViewProjectionMatrixWithSimpleWindow(640,480);
		effekseerManagerCore.Update(1);
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
