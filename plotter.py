import pandas as pd
import plotly.graph_objects as go
import numpy as np
import os

def draw_structure(fig, x_c, y_c, scale=1.0, color='grey', height_scale=1.0):
    w = 25 * scale  
    h = 20 * scale * height_scale 

    x = [x_c-w, x_c+w, x_c+w, x_c-w, x_c-w, x_c+w, x_c+w, x_c-w]
    y = [y_c-w, y_c-w, y_c+w, y_c+w, y_c-w, y_c-w, y_c+w, y_c+w]
    z = [0, 0, 0, 0, h, h, h, h]

    i = [7, 0, 0, 0, 4, 4, 6, 6, 4, 0, 3, 2]
    j = [3, 4, 1, 2, 5, 6, 5, 2, 0, 1, 6, 3]
    k = [0, 7, 2, 3, 6, 7, 1, 1, 5, 5, 7, 6]

    fig.add_trace(go.Mesh3d(
        x=x, y=y, z=z,
        i=i, j=j, k=k,
        color=color, opacity=0.8, flatshading=True, showlegend=False,
        hoverinfo='skip' 
    ))

def add_environment_assets(fig, target_x, target_y):
    theta = np.linspace(0, 2*np.pi, 60)
    r = 200
    fig.add_trace(go.Scatter3d(
        x=target_x + r*np.cos(theta),
        y=target_y + r*np.sin(theta),
        z=np.zeros(60),
        mode='lines',
        line=dict(color='red', width=5),
        name='Zone Objectif',
        hoverinfo='skip'
    ))

    print("Génération de l'environnement urbain...")
    np.random.seed(42) 

    rows, cols = 4, 5  
    spacing_x, spacing_y = 180, 220 

    start_x = target_x - (cols/2 * spacing_x)
    start_y = target_y - (rows/2 * spacing_y)

    for r in range(rows):
        for c in range(cols):
            bx = start_x + c * spacing_x
            by = start_y + r * spacing_y

            jitter = 50
            bx += np.random.uniform(-jitter, jitter)
            by += np.random.uniform(-jitter, jitter)

            b_scale = np.random.uniform(0.8, 1.8)
            b_height = np.random.uniform(0.9, 1.5)
            gray_val = int(np.random.uniform(60, 160))
            b_color = f'rgb({gray_val},{gray_val},{gray_val})'

            draw_structure(fig, bx, by, scale=b_scale, color=b_color, height_scale=b_height)

def main():
    if not os.path.exists('trajectory.csv') or not os.path.exists('landings.csv'):
        print("Erreur: trajectory.csv ou landings.csv introuvable!")
        return

    print("Lecture des données...")
    df_paths = pd.read_csv('trajectory.csv', usecols=['x', 'y', 'z'])[::5]
    df_landings = pd.read_csv('landings.csv', usecols=['x', 'y'])

    avg_x, avg_y = df_landings['x'].mean(), df_landings['y'].mean()

    fig = go.Figure()

    print("Ajout du lanceur...")
    draw_structure(fig, 0, 0, scale=0.7, height_scale=0.6, color='tan')

    add_environment_assets(fig, avg_x, avg_y)

    print(f"Génération des trajectoires et impacts...")
    fig.add_trace(go.Scatter3d(
        x=df_paths['x'], y=df_paths['y'], z=df_paths['z'],
        mode='lines',
        line=dict(color='darkblue', width=1.5), 
        opacity=0.2,
        name='Trajectoires'
    ))

    fig.add_trace(go.Scatter3d(
        x=df_landings['x'], y=df_landings['y'], z=np.zeros(len(df_landings)),
        mode='markers',
        marker=dict(size=3, color='orange', opacity=0.7, symbol='x'),
        name='Impacts'
    ))

    fig.update_layout(
        template="plotly_dark",
        title=dict(text="ANALYSE BALISTIQUE TERMINALE - ENVIRONNEMENT URBAIN", font=dict(color="green")),
        scene=dict(
            xaxis=dict(gridcolor='green', zerolinecolor='green', backgroundcolor='black', title='X (Portée)'),
            yaxis=dict(gridcolor='green', zerolinecolor='green', backgroundcolor='black', title='Y (Latéral)'),
            zaxis=dict(gridcolor='green', zerolinecolor='green', backgroundcolor='black', title='Z (Altitude)'),
            aspectmode='data', 
            camera=dict(
                eye=dict(x=0.8, y=-1.5, z=1.2),
                center=dict(x=0, y=0, z=0)
            )
        ),
        margin=dict(l=0, r=0, b=0, t=50)
    )

    print("Sauvegarde du rapport HTML...")
    output_filename = "simulation_ville.html"
    fig.write_html(output_filename)
    print(f"\nSUCCÈS! Ouvrez '{output_filename}' dans votre navigateur.")

if __name__ == "__main__":
    main()
