{
  description = "SFML Development Environment";

  outputs = { self, nixpkgs }: {
    devShell.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.mkShell {
      buildInputs = [
        nixpkgs.legacyPackages.x86_64-linux.tiled
        nixpkgs.legacyPackages.x86_64-linux.sfml
        nixpkgs.legacyPackages.x86_64-linux.gnumake
      ];
    };
  };
}
