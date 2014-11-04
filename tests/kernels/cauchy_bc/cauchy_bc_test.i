[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
[]

[Variables]
  [./u]
  	order = FIRST
	family = LAGRANGE
	initial_condition = 0.0
  [../]
[]

[Kernels]
  [./accum]
	type = CoefTimeDerivative
	variable = u
	Coefficient = 1.0
  [../]
  [./diff]
    type = CoefDiffusion
    variable = u
	coef = 0.01
  [../]
  [./adv]
    type = Convection
	variable = u
	x = 2.0
	y = 0.0
	z = 0.0
  [../]
[]

[BCs]
  [./left]
    type = VectorCauchyBC
    variable = u
    boundary = 0
    velocity = '2.0 0.0 0.0'
	diffusion = 0.01
	u_in = 1.0
	coupled = u
  [../]
  [./right]
    type = NeumannBC
    variable = u
    boundary = 1
    value = 0
  [../]
[]

[Postprocessors]
  [./u_exit]
    type = AverageNodalVariableValue
    boundary = 1
    variable = u
  [../]

[]

[Executioner]
  type = Transient
  scheme = bdf2
  perf_log = true
  solve_type = 'PJFNK'
  start_time = 0.0
  end_time = 1.0
  dt = 0.01
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Adaptivity]
  marker = ef

  [./Indicators]
    [./error]
      type = GradientJumpIndicator
      variable = u
    [../]
  [../]

  [./Markers]
    [./ef]
      type = ErrorFractionMarker
      indicator = error
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  csv = true
  [./console]
    type = Console
    perf_log = true
    linear_residuals = true
  [../]
[]
