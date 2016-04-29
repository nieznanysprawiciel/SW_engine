﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using System.Windows;
using Microsoft.Win32;

namespace EditorApp
{
	enum EditorState
	{
		Uninitialized
		
	}


	public class Logic
	{
        public PathsManager             PathsManager { get; internal set; }
        public GlobalSettings           GlobalSettings { get; internal set; }
        public Project.ProjectManager   ProjectManager { get; internal set; }
        public Engine.Displayer         Displayer { get; internal set; }

        public MainWindow MainWindowRef { get; internal set; }


		public Logic( MainWindow windowRef )
		{
			MainWindowRef = windowRef;

			PathsManager = new PathsManager();
			GlobalSettings = new GlobalSettings();
			ProjectManager = new Project.ProjectManager( this );
			Displayer = new Engine.Displayer();
		}

		public bool			Init		( string[] cmdArgs )
		{
			PathsManager.InitPaths( cmdArgs );

			if( !Displayer.InitRenderer() )
				return false;

			MainWindowRef.EngineViewport.Source = Displayer.ViewportSurface;
			Displayer.ViewportSurface.SetBackBufferEx( D3DResourceTypeEx.ID3D11Texture2D, Displayer.EngineWrapper.GetRenderTarget( (ushort)MainWindowRef.EngineViewport.Width, (ushort)MainWindowRef.EngineViewport.Height ) );


			string projectPath = ParseCmdLineProject( cmdArgs );
			if( projectPath != null )
				return LoadProject( projectPath );

			return true;
		}

		public bool			LoadProject	( string projectFile )
		{
			PathsManager.UpdateProjectPaths( projectFile );
			bool result = ProjectManager.LoadProject( projectFile );

			if( result )
			{
				MainWindowRef.ActorPreview.DataContext = null;
				MainWindowRef.ActorList.DataContext = ProjectManager.ActorsLogic;
				MainWindowRef.ContentTree.DataContext = ProjectManager.ContentManager;
			}

			return result;
		}

		public void SaveClick( object sender, RoutedEventArgs e )
		{
			ProjectManager.SaveProject();
		}

		public void LoadClick( object sender, RoutedEventArgs e )
		{
			OpenFileDialog fileDialog = new OpenFileDialog();
			fileDialog.CheckFileExists = true;
			fileDialog.CheckPathExists = true;

			fileDialog.DefaultExt = ".swproj";
			fileDialog.Filter = "SW Engine Projects (*.swproj)|*.swproj;";

			Nullable<bool> result = fileDialog.ShowDialog();

			if( result.HasValue && result.Value )
			{
				//var directory = Path.GetDirectoryName( fileDialog.FileName );
				LoadProject( fileDialog.FileName );
			}
		}

		public void			RenderFrame( object sender, EventArgs e )
		{
			Displayer.RenderFrame();
		}

		public void			CloseApplication()
		{
			Displayer.ReleaseRenderer();
		}

		#region PrivateFunctions

		private string		ParseCmdLineProject( string[] cmdArgs )
		{
			if( cmdArgs.Length == 1 )
				return null;

			string projectPath = cmdArgs[ 1 ];
			string fileExtension = Path.GetExtension( projectPath );
			if( fileExtension == GlobalSettings.ProjectFileExt )
				return projectPath;

			return null;
		}


		#endregion
	}
}
